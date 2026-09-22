$ErrorActionPreference = "Stop"

$clang = "C:\Program Files\LLVM\bin\clang.exe"
$serverSource = Join-Path $PSScriptRoot "tcp_server.c"
$clientSource = Join-Path $PSScriptRoot "tcp_client.c"
$serverExe = Join-Path $PSScriptRoot "tcp_server.exe"
$clientExe = Join-Path $PSScriptRoot "tcp_client.exe"

& $clang $serverSource -o $serverExe
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

& $clang $clientSource -o $clientExe
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

$serverProcess = Start-Process -FilePath $serverExe -WorkingDirectory $PSScriptRoot -PassThru -NoNewWindow

try {
    Start-Sleep -Milliseconds 500

    if ($serverProcess.HasExited) {
        throw "The TCP server stopped before the client could connect."
    }

    & $clientExe
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}
finally {
    if (!$serverProcess.HasExited) {
        Stop-Process -Id $serverProcess.Id -Force
    }
}