# Introduction
Tools to make Digital Signal Processing easier

# DSPcruncher

A C-based digital signal processing tool for designing **Finite Impulse Response (FIR) filters using the Window Method**.

## Features

* Low-pass FIR filter
* High-pass FIR filter
* Band-pass FIR filter
* Multiple window functions:

  * Rectangular
  * Hanning
  * Hamming
  * Bartlett
  * Blackman
* Calculates the ideal impulse response (h_d[n])
* Applies the selected window to obtain the final filter coefficients (h[n])
* Displays the resulting transfer function (H(z))

## Compilation

### Linux

Make sure GCC is installed, then compile with:

```bash
gcc -Wall -Wextra -g3 FilterDesign.c -o FilterDesign -lm
```

Run:

```bash
./FilterDesign
```

The `-lm` flag links the C math library, which is required for `sin()` and `cos()`.

### Windows

A precompiled Windows executable can be provided in the **GitHub Releases** section for users who don't want to compile the source themselves.
**Executable for windows will be released soon**

## Usage

Run the program and select:

1. Filter type
2. Number of samples / filter length
3. Window function
4. Cutoff frequency or frequencies as requested

The program then calculates and displays the FIR filter coefficients and corresponding (H(z)).

## Example

For a low-pass filter, the program produces output similar to:

```text
Filter Coefficients h_d[n] = {
    ...
}

H[z] = h[0]z^0 + h[1]z^-1 + ... + h[N-1]z^-(N-1)
```

## Project Status

**Version: v1.0.0**

## License

See the `LICENSE` file for licensing information.
