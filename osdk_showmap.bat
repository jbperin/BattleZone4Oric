@ECHO OFF

::
:: Initial check.
:: Verify if the SDK is correctly configurated
::
IF "%OSDK%"=="" GOTO ErCfg


%osdk%\bin\MemMap.exe build\symbols_RomlessGame map_RomlessGame.htm First %OSDK%\documentation\documentation.css
explorer map_RomlessGame.htm


GOTO End


::
:: Outputs an error message
::
:ErCfg
ECHO == ERROR ==
ECHO The Oric SDK was not configured properly
ECHO You should have a OSDK environment variable setted to the location of the SDK
pause
GOTO End


:End

