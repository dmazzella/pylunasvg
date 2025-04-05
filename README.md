
# Python bindings for lunasvg


## Build
```
git submodule update --init --recursive
```
##### macOS
```zsh
python3 setup.py install
```

##### Windows
```powershell
python setup.py install
```

##### Linux
```bash
python3 setup.py install
```

<details><summary><b>Create Wheels with <b>cibuildwheel</b>:</summary>
<p>

##### macOS
```zsh
python3 -m cibuildwheel --platform macos --output-dir wheels
```

##### Windows
```powershell
python -m cibuildwheel --platform windows --output-dir wheels
```

##### Linux
```bash
python3 -m cibuildwheel --platform linux --output-dir wheels
```

</p>
</details>
