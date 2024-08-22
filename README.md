InputSimulatorCpp
===============
[English](README.md) | [简体中文](README.zh-cn.md)

A Cross Platform (Windows/macOS/Linux) Input Simulator written in C++.

_**The primary purpose of this library:**_

**Mouse**

- Move
- Clicks
- Scrolling of the mouse wheel

**Keyboard**

- Press
- Release
- Key Stroking

## Support Platform

| Platform       | Status |
|----------------|--------|
| Windows        | ✅      |
| macOS          | ✅      |
| Linux(X11)     | ✅      |
| Linux(Wayland) | ❌      |
| Other          | ❌      |

## Linux

### Ubuntu

```bash
sudo apt install -y libx11-dev libxtst-dev
```

## Thanks

* [pythoneer/XInputSimulator](https://github.com/pythoneer/XInputSimulator)
* [usagi/libWRP-key](https://github.com/usagi/libWRP-key)

## License

Based on [GPLv3](LICENSE)
