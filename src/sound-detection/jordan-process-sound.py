import warnings
warnings.simplefilter(action='ignore', category=FutureWarning)
import numpy as np
import matplotlib.pyplot as plt
import os
import IPython.display as ipd
import librosa
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from joblib import dump, load
from pathlib import Path
import pandas as pd

# clapping - 22
# door knock - 30
# car horn - 43
# glass breaking -  39
# clock alarm - 37

project_path = Path('audio/five_class')

def extract_mfccs(file:Path):
    audio, sample_rate = librosa.load(file) 

    #extract mfccs
    mfccs_features = librosa.feature.mfcc(y=audio, n_mfcc=13, sr=sample_rate)
    
    #get average along the time axis
    mfccs_scaled_features = np.mean(mfccs_features,axis=1)
    # mfccs_scaled_features = mfccs_features.flatten('F')
    return mfccs_scaled_features


combined_mfccs = []
labels = []
temp_label = 0
index = 0

for filename in os.listdir(project_path):

    #extract label from filename. Example filename is '1-104089-A-22.wav' where 22 is label
    label_type = int(filename.split('-')[3][:2])

    #clapping
    if (label_type == 22):
        temp_label = 0
    #door knock
    elif (label_type == 30):
        temp_label = 1
    #car horn
    elif (label_type == 43):
        temp_label = 2
    #glass breaking 
    elif (label_type == 39):
        temp_label = 3
    #clock alarm
    elif (label_type == 37):
        temp_label = 4
    else:
        raise Exception("Unrecognized label")
    
    print(f'Computing mfccs for audio sample {index}')
    coeffs = extract_mfccs(project_path / filename )
    combined_mfccs.append(coeffs)
    labels.append(temp_label)
    index = index + 1

combined_mfccs = np.array(combined_mfccs)
labels = np.array(labels)

X_train, X_val, Y_train, Y_val = train_test_split(combined_mfccs,labels,train_size=0.8,test_size=0.2, random_state = 1)#always get the same output

neigh = KNeighborsClassifier(n_neighbors=1)
print('Beginning training...')
neigh.fit(X_train, Y_train)
y_pred_val = neigh.predict(X_val)
print(f'Validation accuracy: {accuracy_score(Y_val,y_pred_val)}')