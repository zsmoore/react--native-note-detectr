import React, { useEffect, useState } from 'react';
import { PermissionsAndroid, Text, View, NativeModules } from 'react-native';

const { NoteDetectr } = NativeModules;

type AndroidAudioModuleProps = {
  isAppActive: boolean;
};

export default (props: AndroidAudioModuleProps) => {
  const [arePermissionsAccepted, setArePermissionsAccepted] = useState(true);
  const [shouldSetupAudio, setShouldSetupAudio] = useState(false);

  useEffect(() => {
    if (!props.isAppActive) {
      return;
    }

    const requestPermissions: () => Promise<void> = async () => {
      try {
        const permissionStatus = await PermissionsAndroid.request(
          PermissionsAndroid.PERMISSIONS.RECORD_AUDIO,
          {
            title: 'Grant Permission To Record Audio?',
            message:
              'This app requires the ability to record audio in order to function.',
            buttonNegative: 'No',
            buttonPositive: 'Yes',
          }
        );
        if (permissionStatus !== PermissionsAndroid.RESULTS.GRANTED) {
          setArePermissionsAccepted(false);
        } else {
          setArePermissionsAccepted(true);
          setShouldSetupAudio(true);
        }
      } catch (err) {
        setArePermissionsAccepted(false);
      }
    };
    if (props.isAppActive) {
      requestPermissions();
    }
  }, [props.isAppActive]);

  useEffect(() => {
    if (shouldSetupAudio && props.isAppActive) {
      NoteDetectr.startStream();
      NoteDetectr.setEnabled();
      NoteDetectr.listenToStream('FrequencyData');
    }
    return () => {
      NoteDetectr.clearAudioObservers();
      NoteDetectr.shutdown();
      NoteDetectr.endStream();
    };
  }, [shouldSetupAudio, props.isAppActive]);

  if (!props.isAppActive) {
    NoteDetectr.clearAudioObservers();
    NoteDetectr.shutdown();
    NoteDetectr.endStream();
    return null;
  }

  if (arePermissionsAccepted === false) {
    return (
      <View>
        <Text>App cannot function without microphone permissions</Text>
      </View>
    );
  } else {
    return null;
  }
};
