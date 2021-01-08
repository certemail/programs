-force killing of dbgsrv
	TASKKILL /IM dbgsrv.exe /F

-find if still using port 5000 after killing:
	NETSTAT -ano | findstr 5000

-force killing of dbgsrv.exe by PID:
	TASKKILL /PID 12345 /F