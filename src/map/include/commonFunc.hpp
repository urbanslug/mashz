/**
 * @file    commonFunc.hpp
 * @author  Chirag Jain <cjain7@gatech.edu>
 */

#ifndef COMMON_FUNC_HPP 
#define COMMON_FUNC_HPP

#include <vector>
#include <algorithm>
#include <deque>
#include <cmath>
#include <fstream>

//Own includes
#include "map/include/map_parameters.hpp"

//External includes
#include "common/murmur3.h"
#include "common/prettyprint.hpp"
#include "common/ALeS.cpp"

namespace skch
{
  /**
   * @namespace skch::CommonFunc
   * @brief     Implements frequently used common functions
   */
  namespace CommonFunc
  {
    //seed for murmerhash
    const int seed = 42;

    /**
     * @brief   reverse complement of kmer (borrowed from mash)
     * @note    assumes dest is pre-allocated
     */
    inline void reverseComplement(const char* src, char* dest, int length) 
    {
      for ( int i = 0; i < length; i++ )
      {    
        char base = src[i];

        switch ( base )
        {    
          case 'A': base = 'T'; break;
          case 'C': base = 'G'; break;
          case 'G': base = 'C'; break;
          case 'T': base = 'A'; break;
          default: break;
        }    

        dest[length - i - 1] = base;
      }    
    }

    /**
     * @brief               convert DNA or AA alphabets to upper case
     * @param[in]   seq     pointer to input sequence
     * @param[in]   len     length of input sequence
     */
    inline void makeUpperCase(char* seq, offset_t len)
    {
      for ( int i = 0; i < len; i++ )
      {
        if (seq[i] > 96 && seq[i] < 123)
        {
          seq[i] -= 32;
        }
      }
    }

    /**
     * @brief   hashing kmer string (borrowed from mash)
     */
    inline hash_t get_spaced_hash(const char* seq, int length, char* spaced_seed)
    {
      std::string new_seq;

      char* s = spaced_seed; const char* q = seq;
      if (length == strlen(spaced_seed)) { // should alaways be true when called rom addMinimizers
        std::cout << "same len" << std::endl;
        for (size_t i=0; i<length; s++, i++, q++) {
          if (*s == '1') new_seq.push_back(*q);
        }

        seq = new_seq.c_str();
        length = strlen(seq);
      }

      char data[16];
      MurmurHash3_x64_128(seq, length, seed, data);

      hash_t hash;

      hash = *((hash_t *)data);

      return hash;
    }


    /**
     * @brief   hashing kmer string (borrowed from mash)
     */
    inline hash_t getHash(const char* seq, int length)
    {
      char data[16];
      MurmurHash3_x64_128(seq, length, seed, data);

      hash_t hash;

      hash = *((hash_t *)data);

      return hash;
    }

    /**
     * @brief       compute winnowed minimizers from a given sequence and add to the index
     * @param[out]  minimizerIndex  minimizer table storing minimizers and their position as we compute them
     * @param[in]   seq             pointer to input sequence
     * @param[in]   len             length of input sequence
     * @param[in]   kmerSize
     * @param[in]   windowSize
     * @param[in]   seqCounter      current sequence number, used while saving the position of minimizer
     */
    template <typename T>
      inline void addMinimizers(std::vector<T> &minimizerIndex, 
          char* seq, offset_t len,
          int kmerSize, 
          int windowSize,
          int alphabetSize,
          seqno_t seqCounter)
      {
        /**
         * Double-ended queue (saves minimum at front end)
         * Saves pair of the minimizer and the position of hashed kmer in the sequence
         * Position of kmer is required to discard kmers that fall out of current window
         */
        std::deque< std::pair<MinimizerInfo, offset_t> > Q;

        makeUpperCase(seq, len);

        // Compute reverse complement of seq
        char* seqRev = new char[len];

        if(alphabetSize == 4) //not protein
          CommonFunc::reverseComplement(seq, seqRev, len);

        // Generate spaced seeds
        uint32_t seed_weight = floor(kmerSize/2);
        uint32_t seed_count = 5;
        char** spaced_seeds = ales::ales_wrapper(seed_weight, seed_count, 0.6, kmerSize);
        std::vector<std::string> selected_spaced_seeds;

        for (uint32_t i=0; i<seed_count; i++) {
          char* current_seed = spaced_seeds[i];
          if (kmerSize == strlen(current_seed)) {
            selected_spaced_seeds.push_back(std::string(current_seed));
          }
        }

        if (selected_spaced_seeds.empty()) {
          std::cerr << "Warning: Spaced seed length is not equal to k-mer size."
                    << " Will not generating a spaced seeds." << std::endl;
        }

        for(offset_t i = 0; i < len - kmerSize + 1; i++)
        {
          // The serial number of current sliding window
          // First valid window appears when i = windowSize - 1
          offset_t currentWindowId = i - windowSize + 1;

          hash_t hashFwd;
          hash_t hashBwd;
          // Hash kmers
          // TODO: wrap in a lambda
          if (selected_spaced_seeds.empty()) {
            hashFwd = CommonFunc::getHash(seq + i, kmerSize);
          } else {
            char* sp = &selected_spaced_seeds[0][0];
            hashFwd = CommonFunc::get_spaced_hash(seq + i, kmerSize, sp);
          }

          if(alphabetSize == 4)
            if (selected_spaced_seeds.empty()) {
              hashBwd = CommonFunc::getHash(seqRev + len - i - kmerSize, kmerSize);
            } else {
              char* sp = &selected_spaced_seeds[0][0];
              hashBwd = CommonFunc::get_spaced_hash(seqRev + len - i - kmerSize, kmerSize, sp);
            }
          else  //proteins
            hashBwd = std::numeric_limits<hash_t>::max();   //Pick a dummy high value so that it is ignored later

          //Consider non-symmetric kmers only
          if(hashBwd != hashFwd)
          {
            //Take minimum value of kmer and its reverse complement
            hash_t currentKmer = std::min(hashFwd, hashBwd);

            //Check the strand of this minimizer hash value
            auto currentStrand = hashFwd < hashBwd ? strnd::FWD : strnd::REV;

            //If front minimum is not in the current window, remove it
            while(!Q.empty() && Q.front().second <=  i - windowSize)
              Q.pop_front();

            //Hashes less than equal to currentKmer are not required
            //Remove them from Q (back)
            while(!Q.empty() && Q.back().first.hash >= currentKmer) 
              Q.pop_back();

            //Push currentKmer and position to back of the queue
            //0 indicates the dummy window # (will be updated later)
            Q.push_back( std::make_pair(
                  MinimizerInfo{currentKmer, seqCounter, 0, currentStrand},
                  i)); 

            //Select the minimizer from Q and put into index
            if(currentWindowId >= 0)
            {
              //We save the minimizer if we are seeing it for first time
              if(minimizerIndex.empty() || minimizerIndex.back() != Q.front().first)
              {
                //Update the window position in this minimizer
                //This step also ensures we don't re-insert the same minimizer again
                Q.front().first.wpos = currentWindowId;     
                minimizerIndex.push_back(Q.front().first);
              }
            }
          }
        }

#ifdef DEBUG
        std::cerr << "INFO, skch::CommonFunc::addMinimizers, inserted minimizers for sequence id = " << seqCounter << "\n";
#endif

        delete [] seqRev;
      }

   /**
     * @brief           Functor for comparing tuples by single index layer
     * @tparam layer    Tuple's index which is used for comparison
     * @tparam op       comparator, default as std::less
     */
    template <size_t layer, template<typename> class op = std::less>
      struct TpleComp
      {
        //Compare two tuples using their values
        template<typename T>
          bool operator() (T const &t1, T const &t2)
          {
            return op<typename std::tuple_element<layer, T>::type>() (std::get<layer>(t1), std::get<layer>(t2));
          }
      };

    /**
     * @brief                   computes the total size of reference in bytes
     * @param[in] refSequences  vector of reference files
     * @return                  total size
     */
    inline uint64_t getReferenceSize(const std::vector<std::string> &refSequences)
    {
      uint64_t count = 0;

      for(auto &f : refSequences)
      {
        //Open the file as binary, and set the position to end
        std::ifstream in(f, std::ifstream::ate | std::ifstream::binary);

        //the position of the current character
        count += (uint64_t)(in.tellg());
      }

      return count;
    }

  }
}

#endif
