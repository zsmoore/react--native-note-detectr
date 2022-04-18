import * as React from 'react';
import { useState } from 'react';

import { StyleSheet, View, Text } from 'react-native';
import AudioModule, { Note } from 'react-native-note-detectr';

export default function App() {
  const [currentNote, setCurrentNote] = useState<Note>();
  return (
    <View style={styles.container}>
      <AudioModule
        isAppActive={true}
        onNoteDetected={(note) => setCurrentNote(note)}
      />
      <Text>{currentNote}</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  box: {
    width: 60,
    height: 60,
    marginVertical: 20,
  },
});
