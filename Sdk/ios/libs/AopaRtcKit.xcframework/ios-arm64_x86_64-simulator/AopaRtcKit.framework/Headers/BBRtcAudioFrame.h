//
//  BBRtcAudioFrame.h
//  products
//
//  Created by bhb on 2021/8/20.
//  Copyright © 2020 banban. All rights reserved.
//


#import <Foundation/Foundation.h>

/** The protocol of the raw audio data.

 @note This protocol applies to iOS only.
 */
@protocol BBRtcAudioDataFrameProtocol <NSObject>
@required

/** Occurs when the recorded audio frame of the local user is received.

 @since v3.4.5

 After you successfully register the audio delegate, the SDK triggers the
 `onRecordAudioFrame` callback every 10 ms by default, and the reported audio
 frame format is the same as the recorded audio frame format.

 **Note**:

 - This callback applies to iOS only.
 - To ensure that the received audio frame has the expected format, you can
 register the
 [getRecordAudioParams]([BBRtcAudioDataFrameProtocol getRecordAudioParams])
 callback when calling the
 [setAudioDataFrame]([BBRtcRtcEngineKit setAudioDataFrame:]) method and set the
 audio recording format in the return value of `getRecordAudioParams`. The SDK
 calculates the sample interval according to the `BBRtcAudioParam` you set in
 the return value of `getRecordAudioParams` and triggers the
 `onRecordAudioFrame` callback at the sample interval.

 @param frame The raw audio data. See BBRtcAudioFrame.

 @return - `YES`: Valid buffer in BBRtcAudioFrame, and the audio frame is
 sent out.
- `NO`: Invalid buffer in BBRtcAudioFrame, and the audio frame is discarded.
 */
- (BOOL)onRecordAudioFrame:(BBRtcAudioFrame* _Nonnull)frame;

/** Occurs when the playback audio frame of all remote users is received.

 @since v3.4.5

 After you successfully register the audio delegate, the SDK triggers the
 `onPlaybackAudioFrame` callback every 10 ms by default, and the reported audio
 frame format is the same as the playback audio frame format.

 **Note**:

 - This callback applies to iOS only.
 - To ensure that the received audio frame has the expected format, you can
 register the
 [getPlaybackAudioParams]([BBRtcAudioDataFrameProtocol getPlaybackAudioParams])
 callback when calling the
 [setAudioDataFrame]([BBRtcRtcEngineKit setAudioDataFrame:]) method and set the
 audio playback format in the return value of `getPlaybackAudioParams`. The SDK
 calculates the sample interval according to the `BBRtcAudioParam` you set in
 the return value of `getPlaybackAudioParams` and triggers the
 `onPlaybackAudioFrame` callback at the sample interval.

 @param frame The raw audio data. See BBRtcAudioFrame.

 @return - `YES`: Valid buffer in BBRtcAudioFrame, and the audio frame is
 sent out.
- `NO`: Invalid buffer in BBRtcAudioFrame, and the audio frame is discarded.
 */
- (BOOL)onPlaybackAudioFrame:(BBRtcAudioFrame* _Nonnull)frame;

/** Occurs when the mixed audio frame of the local user and all remote users
 is received.

 @since v3.4.5

 To trigger this callback, you need to register the
 [getObservedAudioFramePosition]([BBRtcAudioDataFrameProtocol getObservedAudioFramePosition])
 callback when calling the
 [setAudioDataFrame]([BBRtcRtcEngineKit setAudioDataFrame:]) method and set the
 return value of `getObservedAudioFramePosition` as
 `BBRtcAudioFramePositionMixed (1 << 2)`. After the setting is successful, the
 SDK triggers the `onMixedAudioFrame` callback every 10 ms by default, and the
 reported audio frame format is the same as the mixed audio frame format.

 **Note**:

 - This callback applies to iOS only.
 - To ensure that the received audio frame has the expected format, you can
 register the
 [getMixedAudioParams]([BBRtcAudioDataFrameProtocol getMixedAudioParams])
 callback when calling the `setAudioDataFrame` method and set the audio mixing
 format in the return value of `getMixedAudioParams`. The SDK calculates the
 sample interval according to the `BBRtcAudioFrame` you set in the return value
 of `getMixedAudioParams` and triggers the `onMixedAudioFrame` callback at
 the sample interval.

 @param frame The raw audio data. See BBRtcAudioFrame.

 @return - `YES`: Valid buffer in BBRtcAudioFrame, and the audio frame is
 sent out.
- `NO`: Invalid buffer in BBRtcAudioFrame, and the audio frame is discarded.
 */
- (BOOL)onMixedAudioFrame:(BBRtcAudioFrame* _Nonnull)frame;

/** Occurs when the audio frame of a remote user is received before mixing.

 @since v3.4.5

 To trigger this callback, you need to register the
 [getObservedAudioFramePosition]([BBRtcAudioDataFrameProtocol getObservedAudioFramePosition])
 callback when calling the
 [setAudioDataFrame]([BBRtcRtcEngineKit setAudioDataFrame:]) method and set the
 return value of `getObservedAudioFramePosition` as
 `BBRtcAudioFramePositionBeforeMixing (1 << 3)`. After the setting is successful,
 the SDK triggers the `onPlaybackAudioFrameBeforeMixing` callback every 10 ms
 by default, and the reported audio frame format is the same as the playback
 audio frame format.

 @note This callback applies to iOS only.

 @param frame The raw audio data. See BBRtcAudioFrame.
 @param uid The user ID of the remote user.

 @return - `YES`: Valid buffer in BBRtcAudioFrame, and the audio frame is
 sent out.
- `NO`: Invalid buffer in BBRtcAudioFrame, and the audio frame is discarded.
 */
- (BOOL)onPlaybackAudioFrameBeforeMixing:(BBRtcAudioFrame* _Nonnull)frame uid:(NSUInteger)uid;

/** Determines whether to receive raw audio data from multiple channels.

 @since v3.5.0

 After you register the audio frame observer, the SDK triggers this callback
 every time it captures an audio frame.

 In a multi-channel scenario, if you want to get audio data from multiple
 channels, set the return value of this callback as `YES`, and set the return
 value of [getObservedAudioFramePosition]([BBRtcAudioDataFrameProtocol getObservedAudioFramePosition]) as
 `BBRtcAudioFramePositionBeforeMixing (1 << 3)`. After that, the SDK triggers
 the [onPlaybackAudioFrameBeforeMixingEx]([BBRtcAudioDataFrameProtocol onPlaybackAudioFrameBeforeMixingEx:channelId:uid:])
 callback to send you the before-mixing audio data from various channels. You
 can also get the channel ID of each audio frame.

 **Note**

 - Once you set the return value of this callback as `YES`, the SDK triggers
 only the `onPlaybackAudioFrameBeforeMixingEx` callback to send the
 before-mixing audio frame.
 [onPlaybackAudioFrameBeforeMixing]([BBRtcAudioDataFrameProtocol onPlaybackAudioFrameBeforeMixing:uid:])
 is not triggered. In a multi-channel scenario, BBRtc recommends setting the
 return value as `YES`.
 - If you set the return value of this callback as `NO`, the SDK triggers only
 the `onPlaybackAudioFrameBeforeMixing` callback to send the audio data.

 @return - `YES`: Receive audio data from multiple channels.
 - `NO`: Do not receive audio data from multiple channels.
 */
- (BOOL)isMultipleChannelFrameWanted;

/** Gets the audio frame of a remote user before mixing from one of the
 multiple channels.

 @since v3.5.0

 To trigger this callback, you need to register the following callbacks and
 set their return values when calling the
 [setAudioDataFrame]([BBRtcRtcEngineKit setAudioDataFrame:]) method:

 - [getObservedAudioFramePosition]([BBRtcAudioDataFrameProtocol getObservedAudioFramePosition]):
 Set its return value as `BBRtcAudioFramePositionBeforeMixing (1 << 3)`.
 - [isMultipleChannelFrameWanted]([BBRtcAudioDataFrameProtocol isMultipleChannelFrameWanted]):
 Set its return value as `YES`.

 After the setting is successful, the SDK triggers the
 `onPlaybackAudioFrameBeforeMixingEx` callback every 10 ms by default, and the
 reported audio frame format is the same as the playback audio frame format.

 @param frame The raw audio data. See BBRtcAudioFrame.
 @param channelId The channel name.
 @param uid The user ID of the remote user.

 @return - `YES`: Valid buffer in `BBRtcAudioFrame`, and the audio frame is sent out.
 - `NO`: Invalid buffer in `BBRtcAudioFrame`, and the audio frame is discarded.
 */
- (BOOL)onPlaybackAudioFrameBeforeMixingEx:(BBRtcAudioFrame* _Nonnull)frame channelId:(NSString* _Nonnull)channelId uid:(NSUInteger)uid;

/** Sets the audio observation positions.

 @since v3.4.5

 After you successfully register the audio delegate, the SDK uses the
 [getObservedAudioFramePosition]([BBRtcAudioDataFrameProtocol getObservedAudioFramePosition])
 callback to determine at each specific audio-frame processing node whether to
 trigger the following callbacks:

 - [onRecordAudioFrame]([BBRtcAudioDataFrameProtocol onRecordAudioFrame:])
 - [onPlaybackAudioFrame]([BBRtcAudioDataFrameProtocol onPlaybackAudioFrame:])
 - [onMixedAudioFrame]([BBRtcAudioDataFrameProtocol onMixedAudioFrame:])
 - [onPlaybackAudioFrameBeforeMixing]([BBRtcAudioDataFrameProtocol onPlaybackAudioFrameBeforeMixing:uid:])
 or [onPlaybackAudioFrameBeforeMixingEx]([BBRtcAudioDataFrameProtocol onPlaybackAudioFrameBeforeMixingEx:channelId:uid:])

 You can set the positions that you want to observe by modifying the return
 value of `getObservedAudioFramePosition` according to your scenario.

 **Note**:

 - This callback applies to iOS only.
 - To observe multiple positions, use `|` (the OR operator).
 - The default return value of `getObservedAudioFramePosition` is
 `BBRtcAudioFramePositionPlayback (1 << 0)` and
 `BBRtcAudioFramePositionRecord (1 << 1)`.
 - To conserve system resources, you can reduce the number of frame positions
 that you want to observe.

 @return The bit mask that controls the audio observation positions.
 See BBRtcAudioFramePosition.
 */
- (BBRtcAudioFramePosition)getObservedAudioFramePosition;

/** Sets the audio mixing format for the
 [onMixedAudioFrame]([BBRtcAudioDataFrameProtocol onMixedAudioFrame:]) callback.

 @since v3.4.5

 Register the `getMixedAudioParams` callback when calling the
 [setAudioDataFrame]([BBRtcRtcEngineKit setAudioDataFrame:]) method. After you
 successfully register the audio delegate, the SDK triggers this callback each
 time it receives an audio frame. You can set the audio mixing format in
 the return value of this callback.

 **Note**:

 - This callback applies to iOS only.
 - The SDK calculates the sample interval according to the `BBRtcAudioParam`
 you set in the return value of this callback and triggers the
 `onMixedAudioFrame` callback at the calculated sample interval.
 Sample interval (seconds) = `samplesPerCall`/(`sampleRate` × `channel`).
 Ensure that the value of sample interval is equal to or greater than 0.01.

 @return Sets the audio format. See BBRtcAudioParam.
 */
- (BBRtcAudioParam* _Nonnull)getMixedAudioParams;

/** Sets the audio recording format for the
 [onRecordAudioFrame]([BBRtcAudioDataFrameProtocol onRecordAudioFrame:])
 callback.

 @since v3.4.5

 Register the `getRecordAudioParams` callback when calling the
 [setAudioDataFrame]([BBRtcRtcEngineKit setAudioDataFrame:]) method. After you
 successfully register the audio delegate, the SDK triggers this callback each
 time it receives an audio frame. You can set the audio recording format in
 the return value of this callback.

 **Note**:

 - This callback applies to iOS only.
 - The SDK calculates the sample interval according to the `BBRtcAudioParam`
 you set in the return value of this callback and triggers the
 `onRecordAudioFrame` callback at the calculated sample interval.
 Sample interval (seconds) = `samplesPerCall`/(`sampleRate` × `channel`).
 Ensure that the value of sample interval is equal to or greater than 0.01.

 @return Sets the audio format. See BBRtcAudioParam.
 */
- (BBRtcAudioParam* _Nonnull)getRecordAudioParams;

/** Sets the audio playback format for the
 [onPlaybackAudioFrame]([BBRtcAudioDataFrameProtocol onPlaybackAudioFrame:])
 callback.

 @since v3.4.5

 Register the `getPlaybackAudioParams` callback when calling the
 [setAudioDataFrame]([BBRtcRtcEngineKit setAudioDataFrame:]) method. After you
 successfully register the audio delegate, the SDK triggers this callback each
 time it receives an audio frame. You can set the audio playback format in
 the return value of this callback.

 **Note**:

 - This callback applies to iOS only.
 - The SDK calculates the sample interval according to the `BBRtcAudioParam`
 you set in the return value of this callback and triggers the
 `onPlaybackAudioFrame` callback at the calculated sample interval.
 Sample interval (seconds) = `samplesPerCall`/(`sampleRate` × `channel`).
 Ensure that the value of sample interval is equal to or greater than 0.01.

 @return Sets the audio format. See BBRtcAudioParam.
 */
- (BBRtcAudioParam* _Nonnull)getPlaybackAudioParams;

@end
