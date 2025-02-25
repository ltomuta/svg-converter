set APP=%1
del /q testdata\output\complex\*.*
md testdata\output\complex
for %%f in (testdata\input\complex\*.svg) do %APP% %%f testdata\output\complex\%%~nxf

del /q testdata\output\filters\*.*
md testdata\output\filters
for %%f in (testdata\input\filters\*.svg) do %APP% %%f testdata\output\filters\%%~nxf

del /q testdata\output\gradients\*.*
md testdata\output\gradients
for %%f in (testdata\input\gradients\*.svg) do %APP% %%f testdata\output\gradients\%%~nxf

del /q testdata\output\shapes\*.*
md testdata\output\shapes
for %%f in (testdata\input\shapes\*.svg) do %APP% %%f testdata\output\shapes\%%~nxf

del /q testdata\output\misc\*.*
md testdata\output\misc
for %%f in (testdata\input\misc\*.svg) do %APP% %%f testdata\output\misc\%%~nxf
