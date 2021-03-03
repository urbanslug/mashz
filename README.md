# mashz

Compile

```
cmake -H. -Bbuild && cmake --build build -- -j 16
```

Example
--lastz or -z to pass lastz params

```
mashz $LPA $LPA -X -p 95 -t 16 --lastz "--chain --gfextend --nogapped" -V > $PAF_LPA
```
