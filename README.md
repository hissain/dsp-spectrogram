# Spectrogram/ PSD Generation using CMSIS DSP

This project aims to implement spectrogram generation using CMSIS DSP in C/C++. It provides both C code for generating spectrograms utilizing CMSIS DSP library APIs (i.e. FFT, Fast Fourier Transform and so on) and Python code for plotting the spectrograms.

## Folder Structure

- `/python`: Contains Python code for plotting spectrograms.
- `/cmsis`: Contains CMSIS DSP library code for utilized for generating spectrograms.
- `/src`: Contains source code for implementing and testing the spectrogram generation.

## Prerequisites

- CMake
- CMSIS DSP library
- (Optional) Python 3.x/ Jupyter/ Notebook
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
   
5. Run the generated executable to generate spectrogram data. Please refer to src/main.c to understand whats going on and start exploring from there. 
   ```bash
    sh run.sh
    ```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
