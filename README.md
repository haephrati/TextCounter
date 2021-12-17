# TextCounter

Windows utility that counts letters in sentences (including Albanian digraphs) and selects a subset of sentences whose frequencies approach a target table. PDF handling uses a vendored xpdf tree.

## Unit tests

`Tests/TextCounterTests` includes `SentencesCounter.h` and `utils.h` and checks `FIRST_CHAR`, `INF`, default `Node` / `Sentence` state, and `DATEFORMAT`. Build and run:

```
msbuild Tests\TextCounterTests\TextCounterTests.vcxproj /p:Configuration=Release /p:Platform=x64
Tests\TextCounterTests\x64\Release\TextCounterTests.exe
```
