set APP=..\binaries\svg2svgt.exe
del /y testdata\output\complex\*.*
for %%f in (testdata\input\complex\*.svg) do %APP% %%f testdata\output\complex\%%~nxf

del /y testdata\output\filters\*.*
for %%f in (testdata\input\filters\*.svg) do %APP% %%f testdata\output\filters\%%~nxf

del /y testdata\output\gradients\*.*
for %%f in (testdata\input\gradients\*.svg) do %APP% %%f testdata\output\gradients\%%~nxf

del /y testdata\output\shapes\*.*
for %%f in (testdata\input\shapes\*.svg) do %APP% %%f testdata\output\shapes\%%~nxf

del /y testdata\output\misc\*.*
for %%f in (testdata\input\misc\*.svg) do %APP% %%f testdata\output\misc\%%~nxf
