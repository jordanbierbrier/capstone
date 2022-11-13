import matplotlib.pyplot as plt
import numpy as np
from numpy.fft import fft
from scipy.io.wavfile import read, write
from scipy.fftpack import dct

sr,data = read('./output.wav')
print(sr)
plt.plot(data);
plt.title('Signal');
plt.xlabel('Time (samples)');
plt.ylabel('Amplitude');
plt.show()
# data = a numpy array containing the signal to be processed
# fs = a scalar which is the sampling frequency of the data

fft_size = 512
overlap_fac = 0.01
fs = sr
hop_size = np.int32(np.floor(fft_size * (1-overlap_fac)))
pad_end_size = fft_size          # the last segment can overlap the end of the data array by no more than one window size
total_segments = np.int32(np.ceil(len(data) / np.float32(hop_size)))
t_max = len(data) / np.float32(fs)
 
window = np.hanning(fft_size)  # our half cosine window
inner_pad = np.zeros(fft_size) # the zeros which will be used to double each segment size
 
proc = np.concatenate((data, np.zeros(pad_end_size)))              # the data to process
result = np.empty((total_segments, fft_size), dtype=np.float32)    # space to hold the result
 
for i in range(total_segments):                      # for each segment
    current_hop = hop_size * i                        # figure out the current segment offset
    segment = proc[current_hop:current_hop+fft_size]  # get the current segment
    windowed = segment * window                       # multiply by the half cosine function
    padded = np.append(windowed, inner_pad)           # add 0s to double the length of the data
    spectrum = np.fft.fft(padded) / fft_size          # take the Fourier Transform and scale by the number of samples
    autopower = np.abs(spectrum * np.conj(spectrum))  # find the autopower spectrum
    result[i, :] = autopower[:fft_size]               # append to the results array
 
result = 20*np.log10(result)          # scale to db
print(result.shape)
result = np.clip(result, -40, 200)    # clip values
print(result.shape)
img = plt.imshow(result, origin='lower', cmap='jet', interpolation='nearest', aspect='auto')
plt.show()

num_ceps = 12
mfcc = dct(result, type=2, axis=1, norm='ortho')[:, 1 : (num_ceps + 1)] # Keep 2-13
img = plt.imshow(mfcc, origin='lower', cmap='jet', interpolation='nearest', aspect='auto')
plt.show()
mfccs_scaled_features = np.mean(mfcc,axis=0)
print(mfccs_scaled_features)
"""
spec = np.abs(librosa.stft(y, hop_length=512))
spec = librosa.amplitude_to_db(spec, ref=np.max)
librosa.display.specshow(spec, sr=sr, x_axis='time', y_axis='log');
plt.colorbar(format='%+2.0f dB');
plt.title('Spectrogram');

mel_spect = librosa.feature.melspectrogram(y=y, sr=sr, n_fft=2048, hop_length=1024)
mel_spect = librosa.power_to_db(spect, ref=np.max)
librosa.display.specshow(mel_spect, y_axis='mel', fmax=8000, x_axis='time');
plt.title('Mel Spectrogram');
plt.colorbar(format='%+2.0f dB');
"""