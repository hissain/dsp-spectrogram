# Spectrogram Generation using CMSIS DSP

This project implements spectrogram generation using CMSIS DSP in C/C++. It provides both C code for generating spectrograms using CMSIS DSP and Python code for plotting the spectrograms.

## Folder Structure

- `/python`: Contains Python code for plotting spectrograms.
- `/cmsis`: Contains CMSIS DSP code for generating spectrograms.
- `/src`: Contains source code for testing the spectrogram generation.

## Prerequisites

- CMake
- CMSIS DSP library
- Python 3.x
- (Optional) matplotlib (for Python spectrogram plotting from /python folder)

## Usage

1. Clone the repository:

    ```bash
    git clone https://github.com/hissain/dsp-spectrogram.git
    ```

2. Build the CMSIS DSP module using script:

    ```bash
    cd dsp-spectrogram
    cd cmsis
    sh clean.sh
    sh build.sh
    ```
3. Build the Main app using script:
    ```bash
    cd .. #root
    sh clean.sh
    sh build.sh
    ```
   
5. Run the generated executable to generate spectrogram data.
   ```bash
    sh run.sh
    ```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
