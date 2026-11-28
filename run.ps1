param (
    [string] $do_what,
    [string] $path
)    


$env_file = Join-Path $PSScriptRoot ".env"


$ConstPathes = @{
    "cppeasylib" = "godot/client/cppeasylib"
}


if ([string]::IsNullOrWhiteSpace($do_what)) {
    Write-Host "Error: what"
    exit 1
}


if ([string]::IsNullOrWhiteSpace($path)) {
    Write-Host "Error: empty path"
    exit 1
}

if (!(Test-Path $ path -PathType Container))
{
    Write-Host "Error => Dir does not Exist!"
    exit 1
}


switch ($do_what) {
    "build"{
        Push-Location $path
        & scons
    }

    "open"{

    }
}

&scons