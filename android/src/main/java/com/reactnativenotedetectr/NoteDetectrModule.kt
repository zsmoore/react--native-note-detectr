package com.reactnativenotedetectr

import com.facebook.react.bridge.Arguments
import com.facebook.react.module.annotations.ReactModule
import com.reactnativenotedetectr.NoteDetectrModule
import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.bridge.ReactContextBaseJavaModule
import com.facebook.react.bridge.ReactMethod
import com.facebook.react.modules.core.DeviceEventManagerModule

const val NAME = "NoteDetectr"
const val frequencyData = "FREQUENCY_DATA"
@ReactModule(name = NAME)
class NoteDetectrModule(private val reactContext: ReactApplicationContext) : ReactContextBaseJavaModule(reactContext) {
  override fun getName(): String {
    return NAME
  }

  private fun sendFrequencyAudioEvent(eventToPushTo: String, data: Float) {
    val dataMap = Arguments.createMap().apply {
      putDouble(frequencyData, data.toDouble())
    }

    reactContext
      .getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter::class.java)
      .emit(eventToPushTo, dataMap)
  }

  @ReactMethod
  fun startStream() {
    create()
  }

  @ReactMethod
  fun setEnabled() {
    setEnabled(true)
  }

  @ReactMethod
  fun listenToStream(
    frequencyEventID: String,
  ) {
    addObserver { frequency -> sendFrequencyAudioEvent(frequencyEventID, frequency) }
  }

  @ReactMethod
  fun endStream() {
    setEnabled(false)
  }

  @ReactMethod
  fun clearAudioObservers() {
    clearObservers()
  }

  @ReactMethod
  fun shutdown() {
    delete()
  }

  @ReactMethod
  fun addListener(eventName: String?) {
    /* Required for RN built-in Event Emitter Calls. */
  }

  @ReactMethod
  fun removeListeners(count: Int?) {
    /* Required for RN built-in Event Emitter Calls. */
  }

  private external fun create(): Boolean

  private external fun delete()

  private external fun setEnabled(isEnabled: Boolean): Boolean

  private external fun addObserver(audioObserver: AudioObserver): Boolean

  private external fun clearObservers(): Boolean

  companion object {
    init {
      System.loadLibrary("native-lib")
    }
  }
}
