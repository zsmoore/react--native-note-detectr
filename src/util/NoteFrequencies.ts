export enum Note {
  C = 'C',
  CSharp = 'C#',
  D = 'D',
  DSharp = 'D#',
  E = 'E',
  F = 'F',
  FSharp = 'F#',
  G = 'G',
  GSharp = 'G#',
  A = 'A',
  ASharp = 'A#',
  B = 'B',
}

const frequencyMap = new Map<number, Note>([
  [16.35, Note.C],
  [17.32, Note.CSharp],
  [18.35, Note.D],
  [19.45, Note.DSharp],
  [20.6, Note.E],
  [21.83, Note.F],
  [23.12, Note.FSharp],
  [24.5, Note.G],
  [25.96, Note.GSharp],
  [27.5, Note.A],
  [29.14, Note.ASharp],
  [30.87, Note.B],
  [32.7, Note.C],
  [34.65, Note.CSharp],
  [36.71, Note.D],
  [38.89, Note.DSharp],
  [41.2, Note.E],
  [43.65, Note.F],
  [46.25, Note.FSharp],
  [49.0, Note.G],
  [51.91, Note.GSharp],
  [55.0, Note.A],
  [58.27, Note.ASharp],
  [61.74, Note.B],
  [65.41, Note.C],
  [69.3, Note.CSharp],
  [73.42, Note.D],
  [77.78, Note.DSharp],
  [82.41, Note.E],
  [87.31, Note.F],
  [92.5, Note.FSharp],
  [98.0, Note.G],
  [103.83, Note.GSharp],
  [110.0, Note.A],
  [116.54, Note.ASharp],
  [123.47, Note.B],
  [130.81, Note.C],
  [138.59, Note.CSharp],
  [146.83, Note.D],
  [155.56, Note.DSharp],
  [164.81, Note.E],
  [174.61, Note.F],
  [185.0, Note.FSharp],
  [196.0, Note.G],
  [207.65, Note.GSharp],
  [220.0, Note.A],
  [233.08, Note.ASharp],
  [246.94, Note.B],
  [261.63, Note.C],
  [277.18, Note.CSharp],
  [293.66, Note.D],
  [311.13, Note.DSharp],
  [329.63, Note.E],
  [349.23, Note.F],
  [369.99, Note.FSharp],
  [392.0, Note.G],
  [415.3, Note.GSharp],
  [440.0, Note.A],
  [466.16, Note.ASharp],
  [493.88, Note.B],
]);

export default (frequency: number) => {
  var smallestDifference = Number.MAX_SAFE_INTEGER;
  var closestNote: Note | undefined;
  frequencyMap.forEach((note: Note, noteFreq: number) => {
    const difference = Math.abs(frequency - noteFreq);
    if (difference < smallestDifference) {
      smallestDifference = difference;
      closestNote = note;
    }
  });
  return closestNote;
};
