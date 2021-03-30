# mashz

*A DNA sequence read mapper based on mash distances (mashmap) and then base level alignment (lastz).*

mashmap performs approximate matching to somewhat roughly identify similar regions.
We then run lastz runs over these regions to performs base level alignment and
get a more accurate alignment.

## Compile

```
cmake -H. -Bbuild && cmake --build build -- -j 16
```
This will create two binaries in `build/bin` mashz-lastz and mashz.
Make sure mashz-lastz is in your PATH for mashz to find it.

mashz-lastz is just lastz bundled with mashz to ensure compability.
The name mashz-lastz is to avoid conflict with any installed lastz versions.

## Parameters

  - `-l` block length   a minimum length filter for the merged mappings
  - `-s` segment_length length of the mapping seed 
  - `-n` n_secondary    the number of secondary (lower score) mappings to keep default is zero
  - `-p` $map_pct_id    the minimum similarity score for mash distance alignment
  - `-a` $align_pct_id  the minimum similarity score for base level alignment


## Lastz

### lastz specific arguments

Pass arguments to lastz through `--lastz` or `-z` for example
```
mashz target.fa query.fa \
  -X -t 16 -s 50000 -n 10 -p 95 \
  --lastz "--filter=identity:95 --gfextend --chain --gapped" \
  > x.paf
```

#### alignment percentage identity (-a/--align-pct-id)
For better user experience mashz can pass forward to lastz a parameter to filter
out mappings that are below the supplied similarity threshold. 
This parameter (`-a`) is the same as settin
g/passing `--filter=identity:<value>` in lastz.

### hsx index
mashz expects your fasta files to be `hsx` indexed and the hsx indexes in the 
same directory as your fasta file and with the extension `hsx` appeneded to the
fasta filename.

This allows lastz to access sequences within the fasta file based on offsets/coordinates.

To generate a hsx index file use the script `scripts/build_fasta_hsx.py`.
Example:
```
scripts/build_fasta_hsx.py sequence.fa > sequence.fa.hsx
```
