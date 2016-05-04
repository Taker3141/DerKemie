@echo off
rem Do not edit! This batch file is created by CASIO fx-9860G SDK.


if exist KEMIE.G1A  del KEMIE.G1A

cd debug
if exist FXADDINror.bin  del FXADDINror.bin
"X:\CASIO\fx-9860G SDK\OS\SH\Bin\Hmake.exe" Addin.mak
cd ..
if not exist debug\FXADDINror.bin  goto error

"X:\CASIO\fx-9860G SDK\Tools\MakeAddinHeader363.exe" "X:\Projects\DerKemie"
if not exist KEMIE.G1A  goto error
echo Build has completed.
goto end

:error
echo Build was not successful.

:end

