import { NativeEventEmitter, Platform, NativeModules } from 'react-native';
import AndroidAudioModule from './android/AndroidAudioModule';
import GetClosestNote from '../util/NoteFrequencies';
import type { Note } from 'src/util/NoteFrequencies';
import React from 'react';

type AudioModuleProps = {
  isAppActive: boolean;
  onNoteDetected: (note: Note) => void;
};

export default (props: AudioModuleProps) => {
  const module =
    Platform.OS === 'android'
      ? NativeModules.AudioModule
      : NativeModules.iOSAudioModule;
  const eventEmitter = new NativeEventEmitter(module);
  eventEmitter.addListener('FrequencyData', (event) => {
    const frequency = event.FREQUENCY_DATA;
    const closestNote = GetClosestNote(frequency);
    if (closestNote !== undefined) {
      props.onNoteDetected(closestNote);
    }
  });

  const underlyingModule =
    Platform.OS === 'android' ? (
      <AndroidAudioModule isAppActive={props.isAppActive} />
    ) : (
      <AndroidAudioModule isAppActive={props.isAppActive} />
    );

  return underlyingModule;
};
