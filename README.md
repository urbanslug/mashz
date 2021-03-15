# mashz

### Compile

```
cmake -H. -Bbuild && cmake --build build -- -j 16
```

### lastz specific arguments

Pass arguments to lastz through `--lastz` or `-z` for example
```
mashz target.fa query.fa -X -t 16 -s 50000 -n 10 -p 95 --lastz "--filter=identity:95 --gfextend --chain --gapped" > x.paf
```

#### alignment percentage identity (-a/--align-pct-id)
For better user experience mashz can pass forward to lastz a parameter to filter out mappings that are below the supplied similarity threshold. 
Corresponds to --filter=identity:<value> in lastz.

### hsx index

Generate a hsx index for your fasta files and have them next to your fasta files.
These helps lastz read the coordinates in the fasta file as produced by mashmap.
```
scripts/build_fasta_hsx.py sequence.fa > sequence.fa.hsx
```
