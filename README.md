# mashz

Mashz is a merging of mashmap and lastz. 
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
This parameter (`-a`) is the same as setting/passing `--filter=identity:<value>` in lastz.

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
