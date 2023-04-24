# Do not forget to place dll next to this file!

from ctypes import*

api_module = cdll.LoadLibrary("./DLLInjector_API.dll")

process_id = 70500
fullPath_dll = "C:\\Program Files (x86)\\Python310-32\\python310.dll"
if api_module.InjectDLL(process_id, fullPath_dll):
	print("Injected.")
else:
	print("Failed to inject.")