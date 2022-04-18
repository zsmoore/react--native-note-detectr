package com.reactnativenotedetectr

import com.facebook.react.ReactPackage
import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.bridge.NativeModule
import com.facebook.react.uimanager.ViewManager
import java.util.ArrayList
import com.reactnativenotedetectr.NoteDetectrModule

class NoteDetectrPackage : ReactPackage {
  override fun createNativeModules(
    reactContext: ReactApplicationContext
  ) = listOf(NoteDetectrModule(reactContext))

  override fun createViewManagers(
    reactContext: ReactApplicationContext
  ): List<ViewManager<*, *>> = emptyList()
}
