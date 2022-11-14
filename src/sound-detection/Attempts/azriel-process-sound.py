# Initial Attempt

import pyaudio
import torch
import torchaudio
import requests
import pathlib
import wave
# Plot waveform and spectrogram
import matplotlib.pyplot as plt
import os
import librosa
import sklearn
import librosa.display
import numpy as np
from pydub import AudioSegment
from IPython.display import Audio, display

os.environ['KMP_DUPLICATE_LIB_OK']='True'

CHUNK = 1024
FORMAT = pyaudio.paInt16
CHANNELS = 2
RATE = 44100
RECORD_SECONDS = 4
WAVE_OUTPUT_FILENAME = "Input.wav"

p = pyaudio.PyAudio()

stream = p.open(format=FORMAT,
                channels=CHANNELS,
                rate=RATE,
                input=True,
                frames_per_buffer=CHUNK)

print("* recording (You have 4 Seconds)")

frames = []

for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
    data = stream.read(CHUNK)
    frames.append(data)

print("* done recording")

stream.stop_stream()
stream.close()
p.terminate()

wf = wave.open(WAVE_OUTPUT_FILENAME, 'wb')
wf.setnchannels(CHANNELS)
wf.setsampwidth(p.get_sample_size(FORMAT))
wf.setframerate(RATE)
wf.writeframes(b''.join(frames))
wf.close()


# -------------------------------------------------------------------------------
def _plot(waveform, sample_rate, title):
  waveform = waveform.numpy()

  num_channels, num_frames = waveform.shape
  time_axis = torch.arange(0, num_frames) / sample_rate

  figure, axes = plt.subplots(num_channels, 1)
  if num_channels == 1:
    axes = [axes]
  for c in range(num_channels):
    if title == "Waveform":
      axes[c].plot(time_axis, waveform[c], linewidth=1)
      axes[c].grid(True)
    else:
      axes[c].specgram(waveform[c], Fs=sample_rate)
    if num_channels > 1:
      axes[c].set_ylabel(f'Channel {c+1}')
  figure.suptitle(title)
  plt.show(block=False)

def plot_waveform(waveform, sample_rate, title):
  _plot(waveform, sample_rate, title + "Waveform")

def plot_specgram(waveform, sample_rate, title):
  _plot(waveform, sample_rate, title + "Spectrogram")
  
# Normalising the spectral centroid for visualization
def normalize(x, axis=0):
  return sklearn.preprocessing.minmax_scale(x, axis=axis)

def get_spectral_centroid(waveform_data, sample_rate):
  spectral_centroids = librosa.feature.spectral_centroid(waveform_data, sr=sample_rate)[0]
  print(spectral_centroids.shape)
  plt.figure(figsize=(12,4))
  frames = range(len(spectral_centroids))
  t = librosa.frames_to_time(frames)
  
  # Plotting the Spectral centroid along the waveform
  librosa.display.waveplot(waveform_data, sr=sample_rate, alpha=0.4)
  plt.plot(t, normalize(spectral_centroids), color='b')
  
# waveform, sample_rate = torchaudio.load("InputAbraham.wav")
# metadata = torchaudio.info("InputAbraham.wav")

audio = AudioSegment.from_wav("InputAbraham.wav")
audio = audio + 6
audio.export("BoostedInputAbraham.wav", format="wav")
display(Audio("BoostedInputAbraham.wav"))

waveform, sample_rate = librosa.load("BoostedInputAbraham.wav", sr=RATE)

display(Audio("BoostedInputAbraham.wav"))


print(waveform.shape, sample_rate)
# print(metadata)  
# plot_waveform(waveform, sample_rate, "Input Abraham")
# plot_specgram(waveform, sample_rate, "Input Abraham")

get_spectral_centroid(waveform, sample_rate)


# waveform, sample_rate = torchaudio.load("Abraham.wav")
# metadata = torchaudio.info("Abraham.wav")

waveform, sample_rate = librosa.load("Abraham.wav", sr=RATE)

from IPython.display import Audio, display
display(Audio("Abraham.wav"))


print(waveform.shape, sample_rate)
# print(metadata)  
# plot_waveform(waveform, sample_rate, "Base Abraham")
# plot_specgram(waveform, sample_rate, "Base Abraham")

get_spectral_centroid(waveform, sample_rate)

# librosa.load("Abraham.wav", sr=16000)