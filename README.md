# D3D11 and DXGI Detours
This project provides a way to detour functions of D3D11 and DXGI

## Currently Detoured Classes and Functions
### D3D11.dll
* DLL Exported D3D11 Calls
* * D3D11CreateDevice
* * D3D11CreateDeviceAndSwapChain
* ID3D11Device
* ID3D11DeviceContext

### DXGI.dll
* DLL Exported DXGI Calls
* * DXGICreateFactory
* * DXGICreateFactory1
* * DXGICreateFactory2


## Mesh Reconstruction

A seperate project, Chimera, handles the reconstruction of geometry.
