param(
    [Parameter(Mandatory=$true)]
    [string]$Project
)


$Root = $PSScriptRoot

$ProjectDir = Join-Path $Root $Project


if (!(Test-Path $ProjectDir))
{
    Write-Error "Project not found: $Project"
    exit 1
}


$BuildDir = Join-Path $ProjectDir "build"


Write-Host "Building $Project"
Write-Host "Source : $ProjectDir"
Write-Host "Build  : $BuildDir"


# 不进入项目目录
Push-Location $Root


cmake `
    -B "$Project/build" `
    -G Ninja `
    #-DCMAKE_EXPORT_COMPILE_COMMANDS=ON `
    .`


cmake `
    --build "$Project/build"


Pop-Location


Write-Host "Build success."