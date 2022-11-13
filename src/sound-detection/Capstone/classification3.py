#Calculation of MFCCs
import matplotlib.pyplot as plt
import numpy as np
from numpy.fft import fft
from scipy.io.wavfile import read, write
import scipy.fftpack as fft
from scipy.fftpack import dct

sr,audio = read('./download.wav')
print(sr)
plt.plot(audio);
plt.title('Signal');
plt.xlabel('Time (samples)');
plt.ylabel('Amplitude');
plt.show()

#normalizing
overlap_fac = 0.01
max  = np.max(np.abs(audio))
audio = audio/max
frame_size = 0.025
frame_length, frame_step = frame_size * sr, overlap_fac * sr  # Convert from seconds to samples
frame_length = int(round(frame_length))
frame_step = int(round(frame_step))
signal_length = len(audio)
#frame_length = 512
#frame_step = 128
num_frames = int(np.ceil(float(np.abs(signal_length - frame_length)) / frame_step))  # Make sure that we have at least 1 frame

pad_signal_length = num_frames * frame_step + frame_length
z = np.zeros((pad_signal_length - signal_length))
pad_signal = np.append(audio, z) # Pad Signal to make sure that all frames have equal number of samples without truncating any samples from the original signal

indices = np.tile(np.arange(0, frame_length), (num_frames, 1)) + np.tile(np.arange(0, num_frames * frame_step, frame_step), (frame_length, 1)).T
frames = pad_signal[indices.astype(np.int32, copy=False)]

frames *= np.hamming(frame_length)
NFFT = 516
mag_frames = np.absolute(np.fft.rfft(frames, NFFT))  # Magnitude of the FFT
pow_frames = ((1.0 / NFFT) * ((mag_frames) ** 2))  # Power Spectrum
#
nfilt = 40
low_freq_mel = 0
high_freq_mel = (2595 * np.log10(1 + (sr / 2) / 700))  # Convert Hz to Mel
mel_points = np.linspace(low_freq_mel, high_freq_mel, nfilt + 2)  # Equally spaced in Mel scale
hz_points = (700 * (10**(mel_points / 2595) - 1))  # Convert Mel to Hz
bin = np.floor((NFFT + 1) * hz_points / sr)

fbank = np.zeros((nfilt, int(np.floor(NFFT / 2 + 1))))
for m in range(1, nfilt + 1):
    f_m_minus = int(bin[m - 1])   # left
    f_m = int(bin[m])             # center
    f_m_plus = int(bin[m + 1])    # right

    for k in range(f_m_minus, f_m):
        fbank[m - 1, k] = (k - bin[m - 1]) / (bin[m] - bin[m - 1])
    for k in range(f_m, f_m_plus):
        fbank[m - 1, k] = (bin[m + 1] - k) / (bin[m + 1] - bin[m])
filter_banks = np.dot(pow_frames, fbank.T)
filter_banks = np.where(filter_banks == 0, np.finfo(float).eps, filter_banks)  # Numerical Stability
filter_banks = 20 * np.log10(filter_banks)  # dB
img = plt.imshow(filter_banks, origin='lower', cmap='jet', interpolation='nearest', aspect='auto')
plt.show()
#

num_ceps = 12
mfcc = dct(filter_banks, type=2, axis=1, norm='ortho')[:, 1 : (num_ceps + 1)] # Keep 2-13
img = plt.imshow(mfcc.T, origin='lower', cmap='jet', interpolation='nearest', aspect='auto')
plt.show()
mfccs_scaled_features = np.mean(mfcc,axis=0)
print(mfccs_scaled_features)
