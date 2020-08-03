#' Open a void device
#'
#' This function opens a graphic device that accepts inputs, but do not perform
#' any action. As such it is useful for benchmarking graphic code as it removes
#' the device implementation from the implementation.
#'
#' @export
#'
#' @examples
#' void_dev()
#' # Any plotting instructions will now have no effect
#' plot(1:10000, 1:10000)
#' dev.off()
void_dev <- function() {
  invisible(.Call('void_dev', PACKAGE = 'devoid'))
}
