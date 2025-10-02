# ShareNCare

Built as part of CSE-2216 App Dev Lab to learn the Android ecosystem, Firebase, and real‑time communications (WebRTC via CometChat Calls SDK and UIKit).

## Overview

ShareNCare combines an Instagram‑style feed with chat and audio/video calling:
- Authentication with email/password
- Create posts with image or PDF attachments
- Home feed, search, notifications, and profile
- Follow system and basic social interactions
- In‑app chat and audio/video calls powered by CometChat (WebRTC under the hood)
- Push notifications via Firebase Cloud Messaging (FCM)

## Project Structure

- `app` (Android application)
  - Package: `com.example.sharencare`
  - Min SDK 24, Target/Compile SDK 31
  - Uses Firebase (Analytics, Auth, Realtime Database, Storage, Messaging)
  - Integrates CometChat Chat SDK and Calls SDK
  - Navigation with BottomNavigationView and Jetpack Navigation KTX
- `uikit-kotlin` (vendored CometChat Kotlin UI Kit)
  - Provides ready‑made UI for chats and calling flows

## Tech Stack

- Android Jetpack (AppCompat, Material, ConstraintLayout, Navigation)
- Kotlin + Coroutines
- Firebase: Analytics, Auth, Realtime Database, Storage, Cloud Messaging
- CometChat: Pro Android Chat SDK `3.x` and Calls SDK `2.x` (WebRTC based)
- UI/Image: Glide, Picasso, CircleImageView, SkeletonLayout
- Utilities: Volley, TimeAgo

## Prerequisites

- [Android Studio](https://developer.android.com/studio)
- Android SDK Platform 31, build tools 31+ (project uses AGP 7.0.2)
- AVD or physical Android device (Android 7.0, API 24+)

## Setup

1) Firebase
- Create a Firebase project and enable: Authentication (Email/Password), Realtime Database, Storage, and Cloud Messaging.
- Download your `google-services.json` for package `com.example.sharencare` and place it at `app/google-services.json`.

2) CometChat
- Create a CometChat app and obtain: `APP_ID`, `AUTH_KEY`, and region.
- Open `app/src/main/java/com/example/sharencare/constants/AppConfig.kt` and set:
  - `APP_ID`
  - `AUTH_KEY`
  - `REGION`

3) Repositories
- Ensure `settings.gradle` includes the CometChat Maven repo:
  `maven { url "https://dl.cloudsmith.io/public/cometchat/cometchat-pro-android/maven/" }`

## Build & Run

1. Open the project in Android Studio
2. Let Gradle sync. If prompted, install SDKs for API 31
3. Build and run on an emulator or device (API 24+)

Optional: You can sideload an APK from Releases if available.

## Learning Goals and Notes

- Android app architecture with Activities, Fragments, and Jetpack Navigation
- Firebase Auth, Realtime Database, Storage, and FCM basics
- Real‑time chat and audio/video calls using CometChat SDKs (which leverage WebRTC)
- Working with third‑party UI kits (`uikit-kotlin`) and integrating them into an app

## Security

- For personal deployments, use your own Firebase and CometChat credentials. Avoid committing secrets to source control.

## License

This project is for educational purposes as part of CSE‑2216 App Dev Lab.