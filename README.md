
<!-- README.md is generated from README.Rmd. Please edit that file -->

# voidev

This package provides a graphic device that does no operations. This
makes it suitable for benchmarking functions that produce graphics as it
removes the device implementation from the equation. In contrast to the
`nulldev()` function from
[R.devices](https://github.com/HenrikBengtsson/R.devices) package this
device is a true device implementation that simply does nothing rather
than calling `pdf()` with a temporary file connection.

## Installation

You can install `voidev` with the remotes package:

``` r
# install.packages('remotes')
remotes::install_github('r-lib/voidev')
```

## Example

`voidev` provides a single function `void_dev()` which is used much like
any other device:

``` r
library(voidev)

void_dev()
plot(1:10, 1:10)
dev.off()
#> quartz_off_screen 
#>                 2
```
