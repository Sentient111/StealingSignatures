
# Build
## 1. Clone


```bash
git clone https://github.com/flaxyaw/Better-SignatureStealer.git
cd Better-SignatureStealer
```

## 2. Build
### Build using Visual Studio (GUI)

1. CD SignatureStealer-Recode
2. Open the provided .sln file.
3. Change build type to Debug | Release x64
4. Build Project

### Build using msbuild (CLI)
```bash
cd SignatureStealer-Recode
msbuild SignatureStealer-Recode.sln /p:Configuration=Release /p:Platform=x64
cd build
SignatureStealer.exe
```

## 3. Usage

1. Open SignatureStealer.exe
2. Provide the path to an signed PE file
3. Provide the path to an unsigned PE file
4. Check logs for confirmation
5. Confirm by checking the digital signature on unsignedfilename.exe.signed
