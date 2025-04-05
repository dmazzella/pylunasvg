
# Python bindings for lunasvg

## Basic Usage

```python
import pylunasvg

svg = pylunasvg.Document.load_from_file("tiger.svg")
svg.render_to_bitmap().write_to_png("tiger.png")
```

![alt Screen](https://github.com/dmazzella/pylunasvg/blob/main/examples/tiger.png?raw=true)

### More example:
- [examples](https://github.com/dmazzella/pylunasvg/tree/main/examples)

## How to build

<details><summary><b>setuptools</b></summary>
<p>

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

</p>
</details>



<details><summary><b>cibuildwheel</b></summary>
<p>

```
git submodule update --init --recursive
```

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
