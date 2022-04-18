// import { NativeModules, Platform } from 'react-native';
import AudioModule from './module/AudioModule';
export { Note } from './util/NoteFrequencies';

// const LINKING_ERROR =
//   `The package 'react-native-note-detectr' doesn't seem to be linked. Make sure: \n\n` +
//   Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
//   '- You rebuilt the app after installing the package\n' +
//   '- You are not using Expo managed workflow\n';

// const NoteDetectr = NativeModules.NoteDetectr
//   ? NativeModules.NoteDetectr
//   : new Proxy(
//       {},
//       {
//         get() {
//           console.log(NativeModules);
//           throw new Error(LINKING_ERROR);
//         },
//       }
//     );
export default AudioModule;
