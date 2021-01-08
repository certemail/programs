-IDA config files:
	* ida.cfg
	* dbg_windbg.cfg


-Remote Stub:
	ON TARGET:   dbgsrv.exe -t tcp:port=3333
	ON DEBUGGER: "Connection string" ->  tcp:port=3333,PC-TARGET

-Kill remote process (inside windbg)
	.shell TASKKILL /S PC-TARGET /U user /FI "IMAGENAME eq notepad.exe"	

