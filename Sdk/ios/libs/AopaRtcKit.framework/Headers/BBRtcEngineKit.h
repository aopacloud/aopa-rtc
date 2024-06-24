//
//  BBRtcEngineKit.c
//  sources
//
//  Created by bhb on 2020/4/22.
//  Copyright © 2020 banban. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BBRtcMediaIO.h"
#import "BBRtcMediaMetadata.h"
#import "BBRtcAudioFrame.h"
#import "BBRtcVideoFrame.h"


@class BBRtcEngineKit;
@class BBRtcChannel;

/**
 * BBRtc delivers a premium Quality of Experience (QoE) for global voice and video communications over the Internet.
 * It utilizes a virtualized worldwide network, specially designed to enhance real-time interactions across web and mobile platforms.
 *
 * The BBRtcEngineKit serves as the primary interface of the SDK, offering a suite of API methods.
 * These methods are crafted to facilitate straightforward initiation of voice and video communication functionalities within your applications.
 */
@protocol BBRtcEngineDelegate <NSObject>
@optional

#pragma mark Delegate Methods

/**
 * Delegate Methods
 * ----------------
 * The BBRtcEngineDelegate protocol facilitates real-time communication between the SDK and your application
 * by providing delegate methods that respond to runtime events.
 *
 * Starting from version 1.1, the SDK has transitioned from block callbacks to delegate callbacks for improved reliability.
 * While block callbacks are still operational and included in the current release, they are considered deprecated.
 * BBRtc advises migrating to delegate callbacks for all callback functionality.
 * In cases where both block and delegate callbacks are defined, the SDK will prioritize the block callback.
 */

#pragma mark Core Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Core Delegate Methods
 * -----------------------------------------------------------------------------
 */

/**
 * Triggered when the SDK encounters a non-critical issue during execution.
 * Typically, such warnings are informational as the SDK is capable of resolving them autonomously and resuming normal operations.
 * 
 * For example, if the connection to the server is lost, the SDK might report a BBRtcWarningCodeOpenChannelTimeout(106) and will attempt to reconnect.
 * 
 * For more details on warning codes, refer to the BBRtcWarningCode documentation.
 *
 * @param engine The BBRtcEngineKit instance handling the communication.
 * @param warningCode The warning code indicating the type of non-critical issue encountered.
 */

 
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didOccurWarning:(BBRtcWarningCode)warningCode;

/**
 * Indicates a critical error that has occurred within the SDK, which typically requires intervention to resolve.
 * Unlike warnings, these errors prevent the SDK from continuing its operations and may necessitate application-level handling.
 *
 * For instance, if the SDK fails to initialize a call, it will report an error with the code BBRtcErrorCodeStartCall = 1002.
 * In such cases, the application should notify the user of the failure and may need to call the `leaveChannel` method on the BBRtcEngineKit to exit the channel.
 *
 * For a comprehensive list of error codes and their meanings, please refer to the BBRtcErrorCode documentation.
 *
 * @param engine The BBRtcEngineKit instance associated with the error.
 * @param errorCode The error code representing the type of critical issue encountered, as defined in BBRtcErrorCode.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didOccurError:(BBRtcErrorCode)errorCode;

/**
 * Invoked upon the completion of an SDK method execution.
 * 
 * This callback provides the outcome of an API call made by the SDK. It is triggered after the SDK has attempted to execute a method.
 * 
 * @param engine The BBRtcEngineKit instance that executed the method.
 * @param error The BBRtcErrorCode indicating the result of the method call. A return value of 0 suggests a successful call, whereas non-zero values indicate specific errors.
 * @param api The specific API method that was executed by the SDK.
 * @param result A string representing the outcome or result data of the method call. This can include success messages or error details, depending on the execution result.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didApiCallExecute:(NSInteger)error api:(NSString * _Nonnull)api result:(NSString * _Nonnull)result;

/**
 * Called when the local user successfully joins a specified channel.
 *
 * This event is analogous to the `joinSuccessBlock` within the `joinChannelByToken` method, indicating that the user has been added to the channel.
 *
 * @param engine The BBRtcEngineKit instance managing the user's channel entry.
 * @param channel The name of the channel that the local user has joined.
 * @param uid The user ID assigned to the local user. This ID is either provided during the `joinChannelByToken` call or automatically assigned by the server if not specified.
 * @param elapsed The time in milliseconds that has passed since the user initiated the join channel request with `joinChannelByToken` until the callback is triggered by the SDK.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didJoinChannel:(NSString * _Nonnull)channel withUid:(NSUInteger)uid elapsed:(NSInteger) elapsed;

/**
 * Called when the local user successfully rejoins a channel after a network disconnection.
 *
 * If network issues cause the client to lose connection with the server, the SDK will automatically attempt to reconnect.
 * Upon successful reconnection, this callback is triggered, signaling that the user has rejoined the channel with their assigned channel ID and user ID.
 *
 * @param engine The BBRtcEngineKit instance that manages the reconnection process.
 * @param channel The name of the channel to which the user has rejoined.
 * @param uid The user ID of the local user within the channel. This is the same ID that is either specified during the initial `joinChannelByToken` call or automatically assigned by the server if not specified.
 * @param elapsed The duration in milliseconds it took for the reconnection to be established after the initial disconnection occurred.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didRejoinChannel:(NSString * _Nonnull)channel withUid:(NSUInteger)uid elapsed:(NSInteger) elapsed;

/**
 * Triggered when the local user leaves a channel.
 *
 * This callback is activated in response to the application invoking the `leaveChannel` method on the BBRtcEngineKit. It signals to the app that the user has successfully exited the channel.
 *
 * Utilizing this callback, the app can gather various statistics such as the total call duration and data transmission details, including information that might be reported by the `audioQualityOfUid` delegate method to assess the call quality.
 *
 * @param engine The BBRtcEngineKit instance that executed the leave channel operation.
 * @param stats An object containing statistics related to the call, such as duration and data transfer metrics. For more details, refer to the BBRtcChannelStats documentation.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didLeaveChannelWithStats:(BBRtcChannelStats * _Nonnull)stats;

/**
 * Called upon the successful registration of a local user account.
 *
 * This callback is triggered after the application successfully calls either the `registerLocalUserAccount` or `joinChannelByUserAccount` method.
 * It provides the user ID and user account details of the local user who has registered.
 *
 * @param engine The BBRtcEngineKit instance responsible for the registration process.
 * @param userAccount The account identifier associated with the local user.
 * @param uid The unique identifier for the local user.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didRegisteredLocalUser:(NSString * _Nonnull)userAccount withUid:(NSUInteger)uid;

/**
 * Triggered when the SDK acquires the user ID and account information of a remote user.
 *
 * Upon a remote user's entry into the channel, the SDK captures their user ID and account details. These are then stored within a mapping table object (`userInfo`), and this callback is activated on the local client to notify of the update.
 *
 * @param engine The BBRtcEngineKit instance that manages the communication channel.
 * @param userInfo The BBRtcUserInfo object containing the remote user's ID and account information. For details on the structure and content of this object, refer to the BBRtcUserInfo documentation.
 * @param uid The unique identifier for the remote user.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didUpdatedUserInfo:(BBRtcUserInfo * _Nonnull)userInfo withUid:(NSUInteger)uid;

/**
 * Called when the local user's role changes within a live broadcast context.
 *
 * This callback is activated by the SDK when the local user initiates a role change by invoking the `setClientRole` method on the BBRtcEngineKit after having joined the channel.
 * It signifies that the user's role, which can be either a broadcaster or an audience member, has been updated.
 *
 * @param engine The BBRtcEngineKit instance handling the role change.
 * @param oldRole The role that the user is transitioning from, as defined by the BBRtcClientRole enumeration.
 * @param newRole The new role that the user is transitioning to, as defined by the BBRtcClientRole enumeration.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didClientRoleChanged:(BBRtcClientRole)oldRole newRole:(BBRtcClientRole)newRole;

/**
 * Called when the local user's chorus role changes within a KTV session.
 *
 * This callback is triggered by the SDK when the local user changes their chorus role by invoking the `setChorusRole` method on the BBRtcEngineKit after joining the channel.
 * It indicates a transition in the user's role related to chorus functionalities, such as switching between leading a song and accompanying.
 *
 * @param engine The BBRtcEngineKit instance that processes the chorus role change.
 * @param oldRole The previous chorus role of the user, as indicated by the BBRtcChorusRole enumeration.
 * @param newRole The new chorus role of the user, as indicated by the BBRtcChorusRole enumeration.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didChorusRoleChanged:(BBRtcChorusRole)oldRole newRole:(BBRtcChorusRole)newRole;

/**
 * Notifies the app when a remote user or host joins a channel.
 *
 * This callback serves the same purpose as the `userJoinedBlock` in the BBRtcEngineKit.
 * 
 * In a communication scenario, the callback informs the app that a new user has joined the channel, and if there are already users present, it also reports on them.
 * In a live-broadcast scenario, the callback informs the app when a new host joins the channel, with a recommendation to limit the number of hosts to 17.
 *
 * The callback is triggered in the following situations:
 * - When a remote user/host joins the channel via the `joinChannelByToken` method.
 * - When a remote user switches to a host role using the `setClientRole` method after joining.
 * - When a remote user/host reenters the channel following a network disconnection.
 * - When a host introduces an online media stream into the channel with the `addInjectStreamUrl` method.
 *
 * Additional notes for the live-broadcast profile:
 * - Hosts are notified when another host joins the channel.
 * - The audience is notified when a new host joins.
 * - If a web application joins the channel and publishes streams, the callback is triggered for it as well.
 *
 * @param engine The BBRtcEngineKit instance managing the channel events.
 * @param uid The unique identifier of the user or host who has joined the channel. This ID is either predefined in the `joinChannelByToken` method call or auto-assigned by the BBRtc server if not specified.
 * @param elapsed The time in milliseconds elapsed from when the local user initiated the `joinChannelByToken` or `setClientRole` method to when the SDK fires this callback.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didJoinedOfUid:(NSUInteger)uid elapsed:(NSInteger)elapsed;

/**
 * Notifies the app when a remote user or host leaves a channel or goes offline.
 *
 * This callback is equivalent to the `userOfflineBlock` in the BBRtcEngineKit and is triggered in two scenarios:
 *
 * 1. **Leave a channel**: When a user or host intentionally leaves a channel, they send a goodbye message. Upon receipt of this message, the SDK recognizes that the user or host has departed.
 * 2. **Drop offline**: If no data packets are received from the user or host for a certain duration—20 seconds for the Communication profile and a longer period for the Live-broadcast profile—the SDK assumes that the user or host has dropped offline. Note that unreliable network connections might cause false positives; therefore, BBRtc advises implementing a signaling system for more accurate offline detection.
 *
 * @param engine The BBRtcEngineKit instance that manages channel events.
 * @param uid The unique identifier of the user or host who has left the channel or gone offline.
 * @param reason The reason for the user or host going offline, as detailed in the BBRtcUserOfflineReason documentation.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didOfflineOfUid:(NSUInteger)uid reason:(BBRtcUserOfflineReason)reason;

/**
 * Called when there is a change in the network connection state.
 *
 * The SDK utilizes this callback to inform the application about updates in the network connection status, including the cause of the change.
 * This information is crucial for handling network-related events and ensuring smooth communication experience.
 *
 * @param engine The BBRtcEngineKit instance that is monitoring the network connection.
 * @param state An indicator of the current network connection state. For possible states, refer to the BBRtcConnectionStateType documentation.
 * @param reason The factor that has led to the change in the network connection state. More details can be found in the BBRtcConnectionChangedReason documentation.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine connectionChangedToState:(BBRtcConnectionStateType)state reason:(BBRtcConnectionChangedReason)reason;


/**
 * Triggered upon a change in the local network type.
 *
 * This callback is activated when there is a transition in the type of network connection being used by the local device.
 * It serves to identify whether an interruption in the network connection is due to a change in network type or attributable to poor network conditions.
 * Monitoring network type changes is essential for adapting the application's behavior to maintain optimal communication quality.
 *
 * @param engine The BBRtcEngineKit instance responsible for handling network-related events.
 * @param type The new network type that the local device has switched to. For a comprehensive list of network types, refer to the BBRtcNetworkType enumeration.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine networkTypeChangedToType:(BBRtcNetworkType)type;

/**
 * Called when the SDK fails to reconnect to BBRtc's edge server within 10 seconds after its connection is interrupted.
 *
 * This callback is activated by the SDK if it is unable to establish a connection to the server within 10 seconds following the call to `joinChannelByToken`.
 * This can occur whether or not the SDK is currently in a channel.
 *
 * It is important to distinguish this callback from others related to connection issues:
 * - The `rtcEngineConnectionDidInterrupted` callback is triggered when the SDK loses connection with the server for more than four seconds after successfully joining a channel.
 * - The `rtcEngineConnectionDidLost` callback is triggered when the SDK loses connection with the server for more than 10 seconds, irrespective of whether it has joined the channel or not.
 *
 * Note: If the SDK is unable to rejoin the channel within 20 minutes after disconnection from BBRtc's edge server, it will cease attempts to reconnect.
 *
 * @param engine The BBRtcEngineKit instance handling the connection to the server.
 */
- (void)rtcEngineConnectionDidLost:(BBRtcEngineKit * _Nonnull)engine;

/**
 * Called when the token is about to expire in 30 seconds.
 *
 * If the `token` used during the `joinChannelByToken` method call is set to expire, the user will become offline. This callback is triggered by the SDK 30 seconds prior to the token's expiration as a reminder to fetch a new token.
 * 
 * Upon receiving this callback, the application should generate a new `token` on the server. Once obtained, the application should call the `renewToken` method to update the SDK with the fresh `token`.
 *
 * @param engine The BBRtcEngineKit instance responsible for the token management.
 * @param token  The current `token` that will expire in 30 seconds.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine tokenPrivilegeWillExpire:(NSString *_Nonnull)token;

/**
 * Called when the token has expired.
 *
 * If a `token` is used to join a channel by calling the `joinChannelByToken` method and the SDK loses connection to the BBRtc server due to network issues, the `token` may expire after a set period. In such cases, a new `token` is required to reconnect to the server.
 *
 * The SDK triggers this callback to alert the app that it needs to generate a new `token`. To address this, the app should call the `renewToken` method, providing the SDK with the new `token`.
 *
 * @param engine The BBRtcEngineKit instance that is responsible for managing the connection and token.
 */
- (void)rtcEngineRequestToken:(BBRtcEngineKit * _Nonnull)engine;


#pragma mark Media Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Media Delegate Methods
 * -----------------------------------------------------------------------------
 */


/**
 * Reports information about users who are speaking, the volume levels of the speakers, and the voice activity of the local user.
 *
 * This callback is analogous to the `audioVolumeIndicationBlock` provided by the BBRtcEngineKit. It delivers real-time updates about the current loudest speakers in the channel and indicates if the local user is speaking.
 *
 * By default, this feature is inactive. You can activate it by invoking the `enableAudioVolumeIndication` method. Once enabled, the callback operates at specified intervals, regardless of speaking activity.
 *
 * The SDK generates two separate callbacks—reporting on the local user and all remote speakers independently—to provide volume indications. For detailed insights, refer to the parameter descriptions below.
 *
 * **Note:**
 * - To activate voice activity detection for the local user, make sure to set `report_vad(YES)` in the `enableAudioVolumeIndication` method.
 * - The `muteLocalAudioStream` method influences the callback behavior:
 *   - If the local user mutes their stream, the callback for the local user is halted immediately.
 *   - If a remote speaker mutes their stream, after 20 seconds, their information is excluded from the remote speakers' callback. If all remote users mute their streams, after 20 seconds, the callback for remote speakers is terminated.
 *
 * @param engine The BBRtcEngineKit instance that handles audio volume indications.
 * @param speakers An array of BBRtcAudioVolumeInfo objects detailing each speaker's UID, volume, and voice activity detection (VAD) status.
 * - In the local user's callback, the array includes:
 *   - `uid` set to 0,
 *   - `volume` equal to `totalVolume`, reflecting the combined voice and audio mixing volume of the local user, and
 *   - `vad` indicating the voice activity status of the local user.
 * - In the remote speakers' callback, the array includes the `uid` of each remote speaker and their `volume`, with `vad` set to 0. An empty speakers array signifies that no remote users are currently speaking.
 * @param totalVolume The overall mixed volume after audio processing. The value ranges from 0 to 255.
 * - For the local user's callback, `totalVolume` represents the combined voice and audio mixing volume of the local user.
 * - For the remote speakers' callback, `totalVolume` represents the combined voice and audio mixing volume of all remote speakers.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine reportAudioVolumeIndicationOfSpeakers:(NSArray<BBRtcAudioVolumeInfo *> * _Nonnull)speakers totalVolume:(NSInteger)totalVolume;

/** Reports whether the local user is speaking.*/
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine reportLocalAudioVolumeIndication:(BBRtcAudioVolumeInfo *_Nonnull)speaker;

/**
 * Reports the user with the highest accumulative volume over a specific time interval.
 *
 * This callback provides information about the speaker who has the greatest total volume during a measured period. 
 * When a user enables audio volume indication by invoking the `enableAudioVolumeIndication` method, this callback identifies the user ID of the active speaker whose voice is picked up by the SDK's audio volume detection module.
 *
 * **Note:**
 * - To be eligible to receive updates from this callback, you must call the `enableAudioVolumeIndication` method to activate the feature.
 * - Unlike instantaneous volume measurements, this callback reflects the user with the most significant voice volume accumulated over a period, not just at a single moment.
 *
 * @param engine     BBRtcEngineKit object handling the audio volume indications.
 * @param speakerUid The user ID of the speaker with the highest volume. A `speakerUid` of 0 indicates the local user.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine activeSpeaker:(NSUInteger)speakerUid;

/**
 * Called when the engine sends out the first local audio frame.
 *
 * This event is triggered after the local user has successfully joined the channel, indicating that the SDK has started to transmit the user's audio stream.
 *
 * @param engine  BBRtcEngineKit object that manages the audio streaming process.
 * @param elapsed The time in milliseconds elapsed from when the local user initiated the channel join process by calling `joinChannelByToken` until this callback is triggered by the SDK.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine firstLocalAudioFrame:(NSInteger)elapsed;

/**
 * Called when the first local video frame is rendered on the local video view.
 *
 * This event occurs when the SDK first displays the local video stream, indicating that video capture and rendering have successfully started.
 *
 * @param engine  BBRtcEngineKit object that manages the video streaming process.
 * @param size    The dimensions (width and height) of the first local video frame.
 * @param elapsed The time in milliseconds elapsed from the local user initiating the channel join process by calling `joinChannelByToken` until the SDK triggers this callback.
 *
 * If the `startPreview` method is called prior to joining the channel with `joinChannelByToken`, then `elapsed` represents the time from the `startPreview` call to the triggering of this callback.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine firstLocalVideoFrameWithSize:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 * Called when the playback of a remote user's video stream is paused or resumed.
 *
 * This event is triggered when a remote user stops or resumes sending their video stream by invoking the `muteLocalVideoStream` method.
 * You can also monitor video state changes using the `rtcEngine:remoteVideoStateChangedOfUid:state:reason:elapsed:` delegate method with specific state and reason codes.
 *
 * Note that this callback becomes invalid when the channel has more than 20 users or broadcasters.
 *
 * @param engine The BBRtcEngineKit object handling the remote video stream state.
 * @param muted  Indicates whether the remote user's video stream has been paused or resumed.
 *              - YES: The video stream is paused.
 *              - NO: The video stream is resumed.
 * @param uid    The user ID of the remote user whose video stream state has changed.
 */

// Note: The specific state and reason codes are not required in the modified comment.
// They were part of the original comment but have been removed for clarity and brevity.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didVideoMuted:(BOOL)muted byUid:(NSUInteger)uid;

/**
 * Called when the state of audio publishing changes.
 *
 * @since v3.1.0
 *
 * This callback is triggered to notify the application of any changes in the publishing state of the local audio stream.
 * It provides information about the transition from the previous state to the new state, along with the duration of the transition.
 *
 * @param engine    BBRtcEngineKit object that manages the audio streaming process.
 * @param channel   The name of the channel in which the audio publishing state has changed.
 * @param oldState  The previous publishing state of the local audio stream. For possible states, refer to the BBRtcStreamPublishState enumeration.
 * @param newState  The current publishing state of the local audio stream. For possible states, refer to the BBRtcStreamPublishState enumeration.
 * @param elapseSinceLastState The time in milliseconds elapsed since the last state change, indicating the duration of the transition between states.
 */
- (void)rtcEngine:(BBRtcEngineKit* _Nonnull)engine didAudioPublishStateChange:(NSString* _Nonnull)channel oldState:(BBRtcStreamPublishState)oldState newState:(BBRtcStreamPublishState)newState elapseSinceLastState:(NSInteger)elapseSinceLastState;

/**
 * Called when the publishing state of the local video stream changes.
 *
 * @since v3.1.0
 *
 * This callback is triggered to notify the application of any changes in the publishing state of the local video stream.
 * It provides details about the transition from the previous state to the new state and the time taken for this transition.
 *
 * @param engine     BBRtcEngineKit object that manages the video streaming process.
 * @param channel    The name of the channel in which the video publishing state has changed.
 * @param oldState   The previous publishing state of the local video stream. For more information, refer to the BBRtcStreamPublishState enumeration.
 * @param newState   The current publishing state of the local video stream. For more information, refer to the BBRtcStreamPublishState enumeration.
 * @param elapseSinceLastState The time in milliseconds elapsed since the last state change, reflecting the duration of the transition between the old and new states.
 */
- (void)rtcEngine:(BBRtcEngineKit* _Nonnull)engine didVideoPublishStateChange:(NSString* _Nonnull)channel oldState:(BBRtcStreamPublishState)oldState newState:(BBRtcStreamPublishState)newState elapseSinceLastState:(NSInteger)elapseSinceLastState;

/**
 * Called when the subscription state of a remote audio stream changes.
 *
 * @since v3.1.0
 *
 * This callback is triggered to notify the application of any changes in the subscription state of a remote audio stream.
 * It provides information about the transition from the previous state to the new state and the time taken for this transition.
 *
 * @param engine    BBRtcEngineKit object that manages the audio subscription process.
 * @param channel   The name of the channel in which the audio subscription state has changed.
 * @param uid       The user ID of the remote user whose audio subscription state has changed.
 * @param oldState  The previous subscription state of the remote audio stream. For possible states, refer to the BBRtcStreamSubscribeState enumeration.
 * @param newState  The current subscription state of the remote audio stream. For possible states, refer to the BBRtcStreamSubscribeState enumeration.
 * @param elapseSinceLastState The time in milliseconds elapsed since the last state change, indicating the duration of the transition between the old and new states.
 */
- (void)rtcEngine:(BBRtcEngineKit* _Nonnull)engine didAudioSubscribeStateChange:(NSString* _Nonnull)channel withUid:(NSUInteger)uid oldState:(BBRtcStreamSubscribeState)oldState newState:(BBRtcStreamSubscribeState)newState elapseSinceLastState:(NSInteger)elapseSinceLastState;

/**
 * Called when the subscription state of a remote video stream changes.
 *
 * @since v3.1.0
 *
 * This callback is triggered to notify the application of any changes in the subscription state of a remote video stream.
 * It provides details about the transition from the previous state to the new state, including the time elapsed since the last state change.
 *
 * @param engine    BBRtcEngineKit object responsible for managing video subscriptions.
 * @param channel   The name of the channel in which the video subscription state has changed.
 * @param uid       The user ID of the remote user whose video subscription state is changing.
 * @param oldState  The previous subscription state of the remote video stream. For a description of possible states, refer to the BBRtcStreamSubscribeState enumeration.
 * @param newState  The new subscription state of the remote video stream. For a description of possible states, refer to the BBRtcStreamSubscribeState enumeration.
 * @param elapseSinceLastState The time in milliseconds elapsed since the last state change, indicating the duration of the transition between the previous and current states.
 */
- (void)rtcEngine:(BBRtcEngineKit* _Nonnull)engine didVideoSubscribeStateChange:(NSString* _Nonnull)channel withUid:(NSUInteger)uid oldState:(BBRtcStreamSubscribeState)oldState newState:(BBRtcStreamSubscribeState)newState elapseSinceLastState:(NSInteger)elapseSinceLastState;


/**
 * Called when the state of the remote video changes.
 *
 * This callback is triggered to notify the application of any changes in the state of the video stream for a remote user.
 * It includes the new state, the reason for the change, and the elapsed time since the local user joined the channel.
 *
 * @param engine BBRtcEngineKit object that manages the video stream.
 * @param uid The user ID of the remote user whose video state has changed.
 * @param state The new state of the remote video. For a list of possible states, refer to the BBRtcVideoRemoteState enumeration.
 * @param reason The reason for the change in the remote video state. For a list of possible reasons, refer to the BBRtcVideoRemoteStateReason enumeration.
 * @param elapsed The time in milliseconds elapsed since the local user called the `joinChannelByToken` method until the SDK triggers this callback.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine remoteVideoStateChangedOfUid:(NSUInteger)uid state:(BBRtcVideoRemoteState)state reason:(BBRtcVideoRemoteStateReason)reason elapsed:(NSInteger)elapsed;

/**
 * Called when the state of the local video stream changes.
 *
 * The SDK uses this callback to report the current state of the local video stream to the application.
 * It is particularly important to check the `error` parameter when the `state` is BBRtcLocalVideoStreamStateFailed, as it provides details about the failure.
 *
 * @param engine BBRtcEngineKit object that manages the local video stream.
 * @param state The new state of the local video stream. For possible states, refer to the BBRtcLocalVideoStreamState enumeration.
 * @param error Detailed error information if the local video stream has encountered an issue. For possible error codes, refer to the BBRtcLocalVideoStreamError enumeration.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine localVideoStateChange:(BBRtcLocalVideoStreamState)state error:(BBRtcLocalVideoStreamError)error;

/**
 * Called when the local audio stream state changes.
 *
 * This callback is triggered to notify the application of any changes in the state of the local audio stream, 
 * including recording and encoding states. It can be used to monitor the health of the audio stream and troubleshoot issues.
 *
 * @param engine BBRtcEngineKit object that manages the audio stream.
 * @param state The new state of the local audio stream. For possible states, refer to the BBRtcAudioLocalState enumeration.
 * @param error Detailed error information if the local audio stream has encountered an issue. For possible error codes, refer to the BBRtcAudioLocalError enumeration.
 * @param elapsed The time in milliseconds elapsed since the local user started the audio stream until the SDK triggers this callback.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine remoteAudioStateChangedOfUid:(NSUInteger)uid state:(BBRtcAudioRemoteState)state reason:(BBRtcAudioRemoteStateReason)reason elapsed:(NSInteger)elapsed;

/**
 * Called when the state of the local audio stream changes.
 *
 * This callback is triggered to notify the application of any changes in the state of the local audio stream,
 * including audio recording and encoding states. It is an essential tool for monitoring the local audio stream's health
 * and troubleshooting issues when exceptions occur.
 *
 * @param engine The BBRtcEngineKit object that manages the audio stream.
 * @param state  The new state of the local audio stream. For a description of possible states, refer to the BBRtcAudioLocalState enumeration.
 * @param error  Detailed error information if the local audio stream has encountered an issue. For a description of possible error codes, refer to the BBRtcAudioLocalError enumeration.
 *
 * @note When the state is BBRtcAudioLocalStateFailed (value 3), the `error` parameter provides additional details about the failure.
 */

// Note: The actual values and enumerations (BBRtcAudioLocalState, BBRtcAudioLocalError) should be defined elsewhere in the SDK documentation.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine localAudioStateChange:(BBRtcAudioLocalState)state error:(BBRtcAudioLocalError)error;

#pragma mark Fallback Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Fallback Delegate Methods
 * -----------------------------------------------------------------------------
 */

/**
 * Called when the published video stream transitions to audio-only due to poor network conditions or recovers to video when the network improves.
 *
 * If you have called the `setLocalPublishFallbackOption` method of the BBRtcEngineKit and set the option to `BBRtcStreamFallbackOptionAudioOnly`, this callback is triggered in response to changes in the uplink network conditions.
 *
 * @param engine The BBRtcEngineKit object that manages the stream fallback and recovery.
 * @param isFallbackOrRecover Indicates whether the published stream has fallen back to audio-only or recovered to video:
 *   - YES: Indicates the stream has fallen back to audio-only due to unreliable network conditions.
 *   - NO: Indicates the stream has recovered and is now transmitting video after the network conditions have improved.
 *
 * @note Once the published stream falls back to audio-only, the remote application will receive the `userMuteVideoBlock` callback to indicate that the video has been muted.
 */

// Note: The actual callback method names like `setLocalPublishFallbackOption` and `userMuteVideoBlock` should be consistent with the SDK's API documentation.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didLocalPublishFallbackToAudioOnly:(BOOL)isFallbackOrRecover;

/**
 * Called when the remote video stream transitions to audio-only due to poor network conditions or recovers to video when the network improves.
 *
 * If you have called the `setRemoteSubscribeFallbackOption` method of the BBRtcEngineKit and set the option to `BBRtcStreamFallbackOptionAudioOnly`, this callback is triggered in response to changes in the network conditions of the remote media stream.
 *
 * @param engine The BBRtcEngineKit object that manages the remote stream fallback and recovery.
 * @param isFallbackOrRecover Indicates whether the remote media stream has fallen back to audio-only or recovered to video:
 *   - YES: Indicates the stream has fallen back to audio-only due to unreliable network conditions.
 *   - NO: Indicates the stream has recovered and is now transmitting video after the network conditions have improved.
 * @param uid The user ID of the remote user whose stream is affected.
 *
 * @note Once the remote media stream is switched to a low stream (audio-only) due to unreliable network conditions, you can monitor the stream switch between a high stream (video) and low stream (audio-only) in the `rtcEngine:remoteVideoStats:` delegate method.
 */

// Note: The actual callback and method names like `setRemoteSubscribeFallbackOption` and `rtcEngine:remoteVideoStats:` should be consistent with the SDK's API documentation.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didRemoteSubscribeFallbackToAudioOnly:(BOOL)isFallbackOrRecover byUid:(NSUInteger)uid;


#pragma mark Device Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Device Delegate Methods
 * -----------------------------------------------------------------------------
 */

#if (!(TARGET_OS_IPHONE) && (TARGET_OS_MAC))

/** Occurs when the device state changes. (macOS only.)

 @param engine     BBRtcEngineKit object.
 @param deviceId   Device ID.
 @param deviceType Device type: BBRtcMediaDeviceType.
 @param state      State of the device:

 * 0: Added.
 * 1: Removed.
 */
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine device:(NSString * _Nonnull)deviceId type:(BBRtcMediaDeviceType)deviceType stateChanged:(NSInteger) state;

#endif

/**
 * Called when the local audio route changes.
 *
 * This callback is triggered by the SDK whenever there is a change in the audio route used for output on the local device.
 * The change can be to an earpiece, speakerphone, headset, or Bluetooth device, and is indicated by the `routing` parameter.
 *
 * @param engine The BBRtcEngineKit object that manages the audio routing.
 * @param routing The new audio route. For possible routing options, refer to the BBRtcAudioOutputRouting enumeration.
 */

// Note: The BBRtcAudioOutputRouting enumeration should be defined in the SDK documentation with the possible audio route values.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didAudioRouteChanged:(BBRtcAudioOutputRouting)routing;

#if TARGET_OS_IPHONE

/**
 * Called when the camera focus area changes on iOS.
 *
 * This callback is triggered by the SDK when the local user modifies the camera focus position by invoking the `setCameraFocusPositionInPreview` method.
 * It provides the new rectangular area within the camera preview that specifies the focus area.
 *
 * @param engine The BBRtcEngineKit object that manages the camera focus.
 * @param rect   The rectangular area in the camera preview that defines the new focus area.
 */

// Note: The actual method name 'setCameraFocusPositionInPreview' should be consistent with the SDK's API documentation and is correctly referenced here without the use of Markdown links.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine cameraFocusDidChangedToRect:(CGRect)rect;
#endif

#if TARGET_OS_IPHONE
/**
 * Called when the camera exposure area changes on iOS.
 *
 * This callback is triggered by the SDK when the local user adjusts the camera exposure position by invoking the `setCameraExposurePosition` method.
 * It provides the updated rectangular area within the camera preview that specifies the new exposure area.
 *
 * @param engine The BBRtcEngineKit object responsible for camera operations.
 * @param rect   The rectangular area in the camera preview that indicates the exposure area.
 */

// Note: The method 'setCameraExposurePosition' is referenced here without the use of Markdown links, assuming it is correctly named according to the SDK's API documentation.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine cameraExposureDidChangedToRect:(CGRect)rect;
#endif


#pragma mark Statistics Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Statistics Delegate Methods
 * -----------------------------------------------------------------------------
 */

/**
 * Reports the statistics of the current call.
 *
 * The SDK triggers this callback every two seconds after the user joins the channel, providing periodic updates on the call's performance metrics.
 *
 * @param engine The BBRtcEngineKit object that is responsible for the call's statistics.
 * @param stats  The statistics of the BBRtcEngineKit. For details on the statistics reported, refer to the BBRtcChannelStats structure.
 */

// Note: The BBRtcChannelStats should be a documented structure or class within the SDK that contains various statistics about the call's performance.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine reportRtcStats:(BBRtcChannelStats * _Nonnull)stats;

/**
 * Reports the last mile network quality for the local user.
 *
 * This callback provides periodic updates on the connection quality between the local device and the BBRtc edge server. It is triggered once every two seconds before the user joins a channel.
 * The last mile network quality is assessed based on uplink and downlink packet loss rate and jitter, offering insights into potential network issues that may affect the call experience.
 *
 * @param engine The BBRtcEngineKit object responsible for monitoring network quality.
 * @param quality The last mile network quality, which reflects the uplink and downlink conditions. For details on the quality metrics, refer to the BBRtcNetworkQuality enumeration.
 */

// Note: The BBRtcNetworkQuality should be a documented enumeration within the SDK that defines the possible network quality levels based on various metrics.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine lastmileQuality:(BBRtcNetworkQuality)quality;

/**
 * Reports the last mile network quality for each user in the channel.
 *
 * The 'last mile' refers to the connection between the local device and the BBRtc edge server. The SDK provides periodic updates on the last mile network conditions for each user in the channel by triggering this callback once every two seconds. If a channel includes multiple users, this callback is triggered separately for each user.
 *
 * @param engine The BBRtcEngineKit object that manages the network quality reporting.
 * @param uid The user ID of the user whose network quality is being reported. If the `uid` is 0, it reports the local network quality.
 * @param txQuality The uplink transmission quality of the user, which includes metrics such as transmission bitrate, packet loss rate, average Round-Trip Time (RTT), and jitter. This quality rating helps assess how well the current uplink network conditions can support the selected video encoder configuration. For instance, a 1000-Kbps uplink may suffice for 640x480 resolution at 15 fps in the Live-broadcast profile but may not be sufficient for resolutions above 1280x720.
 * @param rxQuality The downlink network quality rating of the user, which includes metrics such as packet loss rate, average RTT, and jitter. This rating indicates the quality of the user's incoming network connection.
 */

// Note: For detailed definitions of network quality metrics, refer to the BBRtcNetworkQuality documentation.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine networkQuality:(NSUInteger)uid txQuality:(BBRtcNetworkQuality)txQuality rxQuality:(BBRtcNetworkQuality)rxQuality;

/**
 * Reports the result of the last-mile network probe test.
 *
 * The SDK initiates this callback to report the outcome of the last-mile network probe test within 30 seconds after the application calls the `startLastmileProbeTest` method. The last-mile refers to the network connection between the local device and the BBRtc edge server.
 *
 * @param engine The BBRtcEngineKit object that is responsible for conducting the network probe test.
 * @param result The result of the uplink and downlink last-mile network probe test, which includes detailed metrics such as round-trip time (RTT), packet loss rate, and jitter. For more information on the result structure, refer to the BBRtcLastmileProbeResult documentation.
 */

// Note: The BBRtcLastmileProbeResult should be a documented class or structure within the SDK that contains the detailed results of the network probe test.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine lastmileProbeTestResult:(BBRtcLastmileProbeResult * _Nonnull)result;

/**
 * Reports the statistics of the uploading local video streams.
 *
 * This callback provides periodic updates on the status of the local video streams being uploaded. It is triggered once every two seconds, offering insights into the performance and quality of the video transmission.
 * It serves the same purpose as the `localVideoStatBlock` callback in the BBRtcEngineKit.
 *
 * @param engine The BBRtcEngineKit object that manages the local video stream statistics.
 * @param stats An object containing the statistics of the uploading local video streams. For details on the statistics provided, refer to the BBRtcLocalVideoStats structure.
 */

// Note: The BBRtcLocalVideoStats should be a documented class or structure within the SDK that includes information such as bitrate, frame rate, and encoding type for the local video stream.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine localVideoStats:(BBRtcLocalVideoStats * _Nonnull)stats;

/**
 * Reports the statistics of the local audio stream.
 *
 * The SDK provides periodic updates on the local audio stream's performance by triggering this callback once every two seconds.
 *
 * @param engine The BBRtcEngineKit object that is responsible for the audio stream.
 * @param stats An object containing the statistics of the local audio stream. For more information on the specific statistics reported, refer to the BBRtcLocalAudioStats structure or class.
 */

// Note: The BBRtcLocalAudioStats should be a documented part of the SDK that includes details such as the audio level, packet loss rate, and other relevant metrics for the local audio stream.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine localAudioStats:(BBRtcLocalAudioStats * _Nonnull)stats;

/**
 * Reports the statistics of the video stream for each remote user/host.
 *
 * The SDK triggers this callback once every two seconds for each remote user/host in the channel. If there are multiple remote users, the callback is triggered separately for each one.
 *
 * This callback provides video transmission quality statistics that are more closely related to the real-user experience compared to the transport layer statistics reported by the `videoTransportStatsOfUid` callback. While this callback focuses on media layer statistics such as frame loss rate, the `videoTransportStatsOfUid` callback provides transport layer statistics like packet loss rate.
 *
 * Schemes like Forward Error Correction (FEC) or retransmission can compensate for frame loss, which may result in an acceptable overall video quality even when the packet loss rate is high.
 *
 * @param engine The BBRtcEngineKit object that manages the video stream statistics.
 * @param stats An array of statistics objects for each received remote video stream. For details on the specific statistics reported, refer to the BBRtcRemoteVideoStats documentation.
 */

// Note: The BBRtcRemoteVideoStats should be a documented class or structure within the SDK that includes details such as frame rate, resolution, and decoding capabilities of the remote video streams.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine remoteVideoStats:(BBRtcRemoteVideoStats * _Nonnull)stats;

/**
 * Reports the statistics of the audio stream for each remote user/host.
 *
 * This callback has replaced the `audioQualityOfUid` callback and now provides more comprehensive insights into the audio transmission quality.
 * The SDK triggers this callback once every two seconds for each remote user/host in the channel. If there are multiple remote users, the callback is triggered separately for each one.
 *
 * Unlike the `audioTransportStatsOfUid` callback, which focuses on transport layer statistics such as packet loss rate, this callback provides media layer statistics that are more closely related to the real-user experience. These include metrics such as frame loss rate, which can be more indicative of perceived audio quality.
 *
 * Error correction schemes like Forward Error Correction (FEC) or retransmission help counter the frame loss rate, potentially resulting in an acceptable overall audio quality even when the packet loss rate is high.
 *
 * @param engine The BBRtcEngineKit object that manages the audio stream statistics.
 * @param stats An array of statistics objects for each received remote audio stream. For details on the specific statistics reported, refer to the BBRtcRemoteAudioStats documentation.
 */

// Note: The BBRtcRemoteAudioStats should be a documented class or structure within the SDK that includes details such as audio level, packet loss rate, and other relevant metrics for the remote audio streams.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine remoteAudioStats:(BBRtcRemoteAudioStats * _Nonnull)stats;



#pragma mark Audio Player Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Audio Player Delegate Methods
 * -----------------------------------------------------------------------------
 */

/**
 * Called when the audio mixing file playback finishes.
 *
 * The SDK triggers this callback to indicate the completion of an audio mixing file playback that was previously started using the `startAudioMixing` method.
 *
 * If the `startAudioMixing` method fails to start the audio mixing, the SDK returns a warning with the code `BBRtcWarningCodeAudioMixingOpenError` in the `didOccurWarning` callback.
 *
 * @param engine The BBRtcEngineKit object that manages the audio mixing playback.
 */
// Note: The actual method and warning code should be consistent with the SDK's API documentation and are referenced here without the use of Markdown links.
- (void)rtcEngineLocalAudioMixingDidFinish:(BBRtcEngineKit * _Nonnull)engine;

/**
 * Called when the state of the local user's audio mixing file changes.
 *
 * This callback provides updates on the audio mixing file's playback status and any errors encountered during playback:
 * - When the audio mixing file starts playing, pauses, or stops, the `state` parameter reflects these actions with corresponding state codes, and the `errorCode` is set to 0 indicating no error.
 * - If an exception occurs during playback, the `state` parameter will indicate this with a specific state code, and the `errorCode` will provide details on the error.
 * - If the local audio mixing file is missing, the SDK does not support the file format, or there is no access to the music file URL, the SDK issues a warning with the code `BBRtcWarningCodeAudioMixingOpenError`.
 *
 * @param engine The BBRtcEngineKit object that manages the audio mixing functionality.
 * @param state  The state code indicating the current status of the audio mixing file. For a list of state codes, refer to the BBRtcAudioMixingStateCode enumeration.
 * @param errorCode The error code providing details on any issues encountered during playback. For a list of error codes, refer to the BBRtcAudioMixingErrorCode enumeration.
 */

// Note: The BBRtcAudioMixingStateCode and BBRtcAudioMixingErrorCode should be documented in the SDK, detailing the meaning of each code related to audio mixing file states and errors.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine localAudioMixingStateDidChanged:(BBRtcAudioMixingStateCode)state errorCode:(BBRtcAudioMixingReasonCode)errorCode;

/**
 * Called when a remote user starts audio mixing.
 *
 * The SDK triggers this callback to notify the application that a remote user has initiated the playback of an audio mixing file.
 * This occurs when the remote user calls the `startAudioMixing` method.
 *
 * @param engine The BBRtcEngineKit object that manages the audio mixing functionality for remote users.
 */

// Note: The actual method name 'startAudioMixing' is referenced here without the use of Markdown links, assuming it is correctly named according to the SDK's API documentation.
- (void)rtcEngineRemoteAudioMixingDidStart:(BBRtcEngineKit * _Nonnull)engine;

/**
 * Called when a remote user finishes audio mixing.
 *
 * The SDK triggers this callback to notify the application that a remote user has completed the playback of their audio mixing file.
 * This event signifies that the audio mixing has ended, either by reaching the end of the audio file or due to a stoppage initiated by the user.
 *
 * @param engine The BBRtcEngineKit object responsible for managing the audio mixing process and triggering this callback.
 */
- (void)rtcEngineRemoteAudioMixingDidFinish:(BBRtcEngineKit * _Nonnull)engine;

/**
 * Called when the local audio effect playback finishes.
 *
 * This callback is triggered by the SDK to indicate the completion of a local audio effect playback that was initiated by calling the `playEffect` method.
 * Each local audio effect is identified by a unique `soundId`.
 *
 * @param engine  The BBRtcEngineKit object that manages the audio effects playback.
 * @param soundId The unique identifier for the local audio effect that has finished playing.
 */

// The specific method 'playEffect' and its parameters are part of the BBRtcEngineKit's API and should be used to start the playback of local audio effects.
- (void)rtcEngineDidAudioEffectFinish:(BBRtcEngineKit * _Nonnull)engine soundId:(NSInteger)soundId;

#pragma mark CDN Publisher Delegate Methods

/**-----------------------------------------------------------------------------
 * @name CDN Live Streaming Delegate Methods
 * -----------------------------------------------------------------------------
 */

/**
 * Called when the state of the RTMP streaming changes.
 *
 * The SDK triggers this callback to report the result of the local user's operations on RTMP streaming, such as adding or removing a streaming URL.
 * This callback provides the current streaming state and the URL associated with the streaming session.
 *
 * The `state` parameter indicates the current status of the RTMP streaming. If an exception occurs, as indicated by the `BBRtcRtmpStreamingStateFailure` state, the `errorCode` parameter offers detailed error information to assist with troubleshooting.
 *
 * @param engine The BBRtcEngineKit object that manages RTMP streaming.
 * @param url    The RTMP streaming URL address.
 * @param state  The current state of the RTMP streaming. For possible states, refer to the BBRtcRtmpStreamingState enumeration.
 * @param errorCode The detailed error code for the streaming session. For possible error codes, refer to the BBRtcRtmpStreamingErrorCode enumeration.
 */

// Note: The BBRtcRtmpStreamingState and BBRtcRtmpStreamingErrorCode are assumed to be part of the SDK's API, detailing the various states and error codes related to RTMP streaming.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine rtmpStreamingChangedToState:(NSString * _Nonnull)url state:(BBRtcRtmpStreamingState)state errorCode:(BBRtcRtmpStreamingErrorCode)errorCode;

/**
 * Called when the CDN live streaming settings are updated.
 *
 * The SDK triggers this callback to report updates to the local host whenever changes are made to the live streaming settings through the `LiveTranscoding` class in the `setLiveTranscoding` method.
 *
 * @note If the `setLiveTranscoding` method is called for the first time to set the `LiveTranscoding` class, the SDK does not trigger the `rtcEngineTranscodingUpdated` callback.
 *
 * @param engine The BBRtcEngineKit object that manages the live streaming settings.
 */

// Note: The specific method 'setLiveTranscoding' and the class 'LiveTranscoding' are part of the BBRtcEngineKit's API for configuring live streaming parameters.
- (void)rtcEngineTranscodingUpdated:(BBRtcEngineKit * _Nonnull)engine;


#pragma mark Inject Stream URL Delegate Methods

/**
 * Reports the status of injecting an online stream into a live broadcast.
 *
 * This callback provides feedback on the process of injecting an external stream into the live broadcast.
 * It is triggered by the status changes of the stream injection, allowing the application to monitor and respond to these changes.
 *
 * @param engine The BBRtcEngineKit object that manages the live broadcast streaming.
 * @param url    The URL address of the externally injected stream.
 * @param uid    The user ID associated with the injected stream.
 * @param status The current status of the externally injected stream. For a description of the status codes, refer to the BBRtcInjectStreamStatus enumeration.
 */

// Note: The BBRtcInjectStreamStatus should be documented in the SDK, detailing the meaning of each status code related to stream injection.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine streamInjectedStatusOfUrl:(NSString * _Nonnull)url uid:(NSUInteger)uid status:(BBRtcInjectStreamStatus)status;

#pragma mark Stream Message Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Stream Message Delegate Methods
 * -----------------------------------------------------------------------------
 */

/**
 * Called when the local user receives a data stream from a remote user within five seconds.
 *
 * This callback is triggered by the SDK when the local user successfully receives a data stream message sent by a remote user.
 * The remote user sends the stream message by invoking the `sendStreamMessage` method.
 *
 * @param engine   BBRtcEngineKit object that manages the data stream communication.
 * @param uid      The user ID of the remote user who sent the message.
 * @param streamId The ID of the data stream.
 * @param data     The data received by the local user from the remote user.
 */

// Note: The `sendStreamMessage` method is part of the BBRtcEngineKit API and is used to send data stream messages to remote users.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine receiveStreamMessageFromUid:(NSUInteger)uid streamId:(NSInteger)streamId data:(NSData * _Nonnull)data;

/**
 * Called when the local user fails to receive a data stream from a remote user within five seconds.
 *
 * The SDK triggers this callback in case of a failure to receive a data stream message that a remote user attempted to send
 * by using the `sendStreamMessage` method. This can happen due to various issues such as network problems or the message being lost.
 *
 * @param engine   BBRtcEngineKit object that manages the data stream communication.
 * @param uid      The user ID of the remote user who attempted to send the message.
 * @param streamId The ID of the data stream associated with the message.
 * @param error    The error code indicating the reason for the failure. For a description of error codes, refer to the BBRtcErrorCode enumeration.
 * @param missed   The number of messages that were lost and not received by the local user.
 * @param cached   The number of incoming messages that were cached during the data stream interruption.
 */

// Note: The `sendStreamMessage` method is part of the BBRtcEngineKit API for sending data stream messages to remote users. Ensure to handle errors and message loss appropriately.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didOccurStreamMessageErrorFromUid:(NSUInteger)uid streamId:(NSInteger)streamId error:(NSInteger)error missed:(NSInteger)missed cached:(NSInteger)cached;

- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didChorusPosition:(NSInteger)position
        timestamp:(NSInteger)timestamp;

#pragma mark Miscellaneous Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Miscellaneous Delegate Methods
 * -----------------------------------------------------------------------------
 */

/**
 * Occurs when the media engine call starts.
 *
 * @param engine The BBRtcEngineKit object that manages the media engine operations.
 */
- (void)rtcEngineMediaEngineDidLoaded:(BBRtcEngineKit * _Nonnull)engine;

/**
 * Triggered when the media engine initiates a call.
 *
 * This callback indicates the commencement of operations within the media engine, signaling the start of a call process.
 *
 * @param engine The BBRtcEngineKit instance responsible for the media engine functionality.
 */
- (void)rtcEngineMediaEngineDidStartCall:(BBRtcEngineKit * _Nonnull)engine;


/**
 * Called when the state of the media stream relay changes.
 *
 * This callback is triggered by the SDK to report the current state of the media relay and to provide any potential error messages.
 * It is an essential tool for monitoring the status of media stream relay operations and for error handling.
 *
 * @param engine The BBRtcEngineKit object that manages the media stream relay.
 * @param state  The state code indicating the current status of the media relay. For a description of the state codes, refer to the BBRtcChannelMediaRelayState enumeration.
 * @param error  The error code providing details on any issues encountered during the media relay. For a description of the error codes, refer to the BBRtcChannelMediaRelayError enumeration.
 */

// Note: The BBRtcChannelMediaRelayState and BBRtcChannelMediaRelayError are assumed to be part of the SDK's API, detailing the various states and error codes related to media stream relay.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine channelMediaRelayStateDidChange:(BBRtcChannelMediaRelayState)state error:(BBRtcChannelMediaRelayError)error;

/**
 * Reports events occurring during the media stream relay process.
 *
 * This callback serves to inform the application of various events that may happen while relaying the media stream.
 * Monitoring these events can help in understanding the flow and any issues that might arise during the relay.
 *
 * @param engine The BBRtcEngineKit object that is responsible for the media stream relay operations.
 * @param event  The event code representing the specific media stream relay event. For a detailed description of the event codes, refer to the BBRtcChannelMediaRelayEvent enumeration.
 */

// Note: The BBRtcChannelMediaRelayEvent enumeration should be documented in the SDK, providing details on the types of events that can occur during media stream relay.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didReceiveChannelMediaRelayEvent:(BBRtcChannelMediaRelayEvent)event;


#pragma mark Deprecated Delegates

/**
 * Called when the first remote video frame is rendered.
 *
 * This callback is triggered by the SDK when the first video frame from a remote user is successfully rendered.
 * It signifies that the remote video stream has started playing on the local device.
 *
 * @param engine  BBRtcEngineKit object that manages the video rendering process.
 * @param uid     The user ID of the remote user who is sending the video stream.
 * @param size    The size of the video frame, indicating its width and height.
 * @param elapsed The time in milliseconds elapsed from when the local user joined the channel until this callback is triggered by the SDK.
 *                This timing starts from the moment the local user calls the `joinChannelByToken` method.
 */

// Note: The `firstRemoteVideoFrameBlock` is a callback provided by the BBRtcEngineKit for monitoring the rendering of the first remote video frame.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine firstRemoteVideoFrameOfUid:(NSUInteger)uid size:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 * Called when the engine receives the first audio frame from a specified remote user.
 *
 * This callback is triggered under the following scenarios:
 * - When a remote user joins the channel and begins sending an audio stream.
 * - When a remote user who has stopped sending the audio stream resumes sending it after 15 seconds. This can occur if:
 *   - The remote user leaves the channel and re-joins.
 *   - The remote user's connection drops and then recovers.
 *   - The remote user mutes their local audio stream using the `muteLocalAudioStream` method.
 *   - The remote user disables audio using the `disableAudio` method.
 *
 * @param engine  BBRtcEngineKit object that manages audio streams.
 * @param uid     The user ID of the remote user from whom the first audio frame is received.
 * @param elapsed The time in milliseconds elapsed from when the local user joined the channel until the SDK triggers this callback.
 *                This timing starts from the moment the local user calls the `joinChannelByToken` method.
 */

// Note: The methods `muteLocalAudioStream` and `disableAudio` are part of the BBRtcEngineKit API and are used to control the local audio stream.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine firstRemoteAudioFrameOfUid:(NSUInteger)uid elapsed:(NSInteger)elapsed;

/**
 * Called when the SDK decodes the first remote audio frame for playback.
 *
 * This callback is triggered under the following circumstances:
 * - When a remote user joins the channel and starts sending an audio stream.
 * - When a remote user who has stopped sending the audio stream resumes sending it after 15 seconds. Possible reasons for the interruption include:
 *   - The remote user leaves the channel.
 *   - The remote user's connection is lost.
 *   - The remote user mutes their local audio stream by calling the `muteLocalAudioStream` method.
 *   - The remote user disables audio entirely by calling the `disableAudio` method.
 *
 * @param engine The BBRtcEngineKit object that manages audio operations.
 * @param uid The user ID of the remote user who is sending the audio stream.
 * @param elapsed The time in milliseconds elapsed from when the local user calls the `joinChannel` method until this callback is triggered by the SDK.
 */

// Note: The `muteLocalAudioStream` and `disableAudio` methods are part of the BBRtcEngineKit API, used to control the sending of the local audio stream.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine firstRemoteAudioFrameDecodedOfUid:(NSUInteger)uid elapsed:(NSInteger)elapsed;

/**
 * Called when a remote user's audio stream is muted or unmuted.
 *
 * The SDK triggers this callback to notify the application of changes in the audio streaming status of a remote user.
 * This occurs when the remote user mutes or unmutes their audio stream by invoking the `muteLocalAudioStream` method.
 *
 * @note This callback becomes invalid when the channel has more than 20 users or broadcasters.
 * @param engine The BBRtcEngineKit object that manages audio streams.
 * @param muted  The new state of the remote user's audio stream:
 *               - YES: The audio stream is now muted.
 *               - NO: The audio stream is now unmuted.
 * @param uid    The user ID of the remote user whose audio stream state has changed.
 */

// Note: The `muteLocalAudioStream` method is part of the BBRtcEngineKit API for controlling the transmission of the local audio stream.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didAudioMuted:(BOOL)muted byUid:(NSUInteger)uid;

/**
 * Reports the result of the addPublishStreamUrl method call.
 *
 * This callback provides the outcome of attempting to add a new RTMP publishing URL to the live stream.
 * It is triggered in response to the `addPublishStreamUrl:transcodingEnabled:` method call.
 *
 * @param engine    The BBRtcEngineKit object that manages the live streaming process.
 * @param url       The RTMP URL address for which the publishing result is reported.
 * @param errorCode The error code indicating the result of the operation. For a list of error codes, refer to the BBRtcErrorCode enumeration. Main errors include:
 *                  - BBRtcErrorCodeNoError(0): Publishing succeeded.
 *                  - BBRtcErrorCodeFailed(1): Publishing failed.
 *                  - BBRtcErrorCodeInvalidArgument(2): An invalid argument was used, such as not configuring BBRtcLiveTranscoding before adding the URL.
 *                  - BBRtcErrorCodeTimedOut(10): Publishing timed out.
 *                  - BBRtcErrorCodeAlreadyInUse(19): The RTMP URL is already in use for CDN live streaming.
 *                  - BBRtcErrorCodeAbort(20): The SDK disconnected from the CDN server, stopping the live stream.
 *                  - BBRtcErrorCodeResourceLimited(22): Insufficient backend resources for CDN live streaming.
 *                  - BBRtcErrorCodeEncryptedStreamNotAllowedPublish(130): Cannot publish an encrypted stream.
 *                  - BBRtcErrorCodePublishStreamCDNError(151): CDN-related errors; remove and re-add the URL to resolve.
 *                  - BBRtcErrorCodePublishStreamNumReachLimit(152): Exceeded the limit of 10 published URLs for the host.
 *                  - BBRtcErrorCodePublishStreamNotAuthorized(153): Unauthorized manipulation of other hosts' URLs.
 *                  - BBRtcErrorCodePublishStreamInternalServerError(154): Internal server error; retry publishing.
 *                  - BBRtcErrorCodePublishStreamFormatNotSuppported(156): Unsupported RTMP stream URL format.
 */

// Note: The BBRtcErrorCode enumeration should be documented in the SDK, detailing the meaning of each error code related to live streaming operations.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine streamPublishedWithUrl:(NSString * _Nonnull)url errorCode:(BBRtcErrorCode)errorCode;

/**
 * Reports the result of removing an RTMP stream from the CDN.
 *
 * This callback is triggered after attempting to remove an RTMP publishing URL from the CDN using the `removePublishStreamUrl:` method.
 * It indicates whether the operation to remove the RTMP stream was successful.
 *
 * @param engine The BBRtcEngineKit object that manages the live streaming process.
 * @param url    The RTMP URL address from which the stream has been removed or attempted to be removed.
 */

// Note: Ensure to handle the result of the `removePublishStreamUrl:` operation to maintain the correct state of your live streaming setup.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine streamUnpublishedWithUrl:(NSString * _Nonnull)url;

/**
 * Reports the transport-layer statistics of each remote audio stream.
 *
 * **DEPRECATED** from v2.9.0. It is recommended to use the `rtcEngine:remoteAudioStats:` callback instead for more comprehensive statistics.
 *
 * This deprecated callback provided transport-layer statistics such as packet loss rate and network time delay for each remote audio stream.
 * It was triggered once every two seconds after the local user received an audio packet from a remote user.
 *
 * @param engine  The BBRtcEngineKit object that manages audio streams.
 * @param uid     The user ID of the remote user who sent the audio packet.
 * @param delay   The network time delay in milliseconds from when the remote user sent the audio packet to when it was received by the local user.
 * @param lost    The packet loss rate in percentage of the audio packet sent from the remote user.
 * @param rxKBitRate The received bitrate in Kbps of the audio packet sent from the remote user.
 */

// Note: The `rtcEngine:remoteAudioStats:` callback offers an updated and recommended approach for retrieving remote audio statistics.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine audioTransportStatsOfUid:(NSUInteger)uid delay:(NSUInteger)delay lost:(NSUInteger)lost rxKBitRate:(NSUInteger)rxKBitRate;

/**
 * Reports the transport-layer statistics of each remote video stream.
 *
 * **DEPRECATED** from v2.9.0. It is recommended to use the `rtcEngine:remoteVideoStats:` callback instead for more comprehensive statistics.
 *
 * This deprecated callback provided transport-layer statistics such as packet loss rate and network time delay for each remote video stream.
 * It was triggered once every two seconds after the local user received a video packet from a remote user.
 *
 * @param engine  The BBRtcEngineKit object that manages video streams.
 * @param uid     The user ID of the remote user who sent the video packet.
 * @param delay   The network time delay in milliseconds from when the remote user sent the video packet to when it was received by the local user.
 * @param lost    The packet loss rate in percentage of the video packet sent from the remote user.
 * @param rxKBitRate The received bitrate in Kbps of the video packet sent from the remote user.
 */

// Note: The `rtcEngine:remoteVideoStats:` callback offers an updated and recommended approach for retrieving remote video statistics.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine videoTransportStatsOfUid:(NSUInteger)uid delay:(NSUInteger)delay lost:(NSUInteger)lost rxKBitRate:(NSUInteger)rxKBitRate;

/**
 * Occurs when a specific remote user enables or disables the video module.
 *
 * **DEPRECATED** from v2.9.0. This callback has been deprecated in favor of the `rtcEngine:remoteVideoStateChangedOfUid:state:reason:elapsed:` callback.
 * For updated functionality, use the new callback with the following parameters to detect changes in the remote user's video state:
 * - BBRtcVideoRemoteStateStopped(0) with BBRtcVideoRemoteStateReasonRemoteMuted(5) for muted video.
 * - BBRtcVideoRemoteStateDecoding(2) with BBRtcVideoRemoteStateReasonRemoteUnmuted(6) for unmuted video.
 *
 * Once the video module is disabled for a remote user, they can only participate in voice calls and cannot send or receive video streams.
 *
 * The SDK would have triggered this callback when the remote user enabled or disabled the video module by calling the `enableVideo` or `disableVideo` method.
 *
 * @param engine  The BBRtcEngineKit object that manages user media streams.
 * @param enabled The state of the remote user's video module:
 *                - YES: The video module is enabled, and the remote user can participate in a video session.
 *                - NO: The video module is disabled, restricting the remote user to voice-only sessions with no video transmission.
 * @param uid     The user ID of the remote user whose video module state has changed.
 */

// Note: With the deprecation of this callback, developers should migrate to using the `rtcEngine:remoteVideoStateChangedOfUid:state:reason:elapsed:` callback to handle remote video state changes.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didVideoEnabled:(BOOL)enabled byUid:(NSUInteger)uid;

/**
 * Occurs when a specific remote user enables or disables their local video capturing function.
 *
 * **DEPRECATED** from v2.9.0. This callback has been deprecated and is replaced by the `rtcEngine:remoteVideoStateChangedOfUid:state:reason:elapsed:` callback.
 * For updated functionality, use the new callback with the following parameters to detect changes in the remote user's video state:
 * - `BBRtcVideoRemoteStateStopped(0)` with `BBRtcVideoRemoteStateReasonRemoteMuted(5)` for when the remote video is muted.
 * - `BBRtcVideoRemoteStateDecoding(2)` with `BBRtcVideoRemoteStateReasonRemoteUnmuted(6)` for when the remote video is unmuted.
 *
 * This callback is particularly relevant in scenarios where a user wishes to only view remote videos and not send their own video stream to others.
 *
 * @param engine  The BBRtcEngineKit object responsible for managing media streams.
 * @param enabled The status of the remote user's local video capturing function:
 *                - YES: Enabled, meaning other users in the channel can see the video of this remote user.
 *                - NO: Disabled, meaning other users in the channel do not receive the video stream from this remote user, although the remote user can still receive video streams from others.
 * @param uid     The user ID of the remote user whose local video capturing function has been enabled or disabled.
 */

// Note: With the deprecation of this callback, developers should transition to using the `rtcEngine:remoteVideoStateChangedOfUid:state:reason:elapsed:` callback to monitor changes in the video capturing state of remote users.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didLocalVideoEnabled:(BOOL)enabled byUid:(NSUInteger)uid;

/**
 * Called when the first remote video frame is received and decoded.
 *
 * **DEPRECATED** from v2.9.0. It is recommended to use the `BBRtcVideoRemoteStateStarting(1)` or `BBRtcVideoRemoteStateDecoding(2)` states in the `rtcEngine:remoteVideoStateChangedOfUid:state:reason:elapsed:` callback instead.
 *
 * This callback was triggered in the following scenarios:
 * - When a remote user joined the channel and started sending a video stream.
 * - When a remote user who had stopped sending the video stream resumed sending it after 15 seconds. Reasons for re-sending the video stream may include:
 *   - The remote user rejoined the channel.
 *   - The remote user regained connection after going offline.
 *   - The remote user called `muteLocalVideoStream` to stop and then restart sending the local video stream.
 *   - The remote user called `disableVideo` and then re-enabled video.
 *
 * @param engine  The BBRtcEngineKit object that manages video streams.
 * @param uid     The user ID of the remote user who sent the video stream.
 * @param size    The size of the video frame, specified by its width and height.
 * @param elapsed The time elapsed in milliseconds from when the local user called the `joinChannelByToken` method until the SDK triggered this callback.
 */

// Note: Since this callback has been deprecated, developers should now use the `rtcEngine:remoteVideoStateChangedOfUid:state:reason:elapsed:` callback to handle events related to the reception and decoding of the first remote video frame.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine firstRemoteVideoDecodedOfUid:(NSUInteger)uid size:(CGSize)size elapsed:(NSInteger)elapsed;

/**
 * Called when the microphone capture is enabled or disabled.
 *
 * **DEPRECATED** from v2.9.0. It is recommended to use the `localAudioStateChange` callback with `BBRtcAudioLocalStateStopped(0)` or `BBRtcAudioLocalStateRecording(1)` states instead.
 *
 * The SDK would have triggered this callback when the local user enabled or disabled the capture of the local audio stream by calling the `enableLocalAudio` method.
 *
 * @param engine  The BBRtcEngineKit object that manages audio settings.
 * @param enabled The status of the microphone:
 *                - YES: The microphone is enabled, and the local audio stream is being captured.
 *                - NO: The microphone is disabled, and the capture of the local audio stream is stopped.
 */

// Note: Since this callback has been deprecated, developers should now use the `rtcEngine:localAudioStateChange:error:` callback to handle changes in the local audio capture state.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine didMicrophoneEnabled:(BOOL)enabled;

/**
 * Called when the connection between the SDK and the server is interrupted.
 *
 * **DEPRECATED** from v2.3.2. It is recommended to use the `connectionChangedToState` callback instead.
 *
 * The SDK would have triggered this callback when it lost connection with the server for more than four seconds after an established connection.
 * Following this event, the SDK attempts to reconnect to the server, and this callback could be used to implement notifications for the user.
 *
 * This callback differs from `rtcEngineConnectionDidLost` in the following ways:
 * - The `rtcEngineConnectionDidInterrupted` callback is triggered when the connection to the server is lost for more than four seconds after joining the channel.
 * - The `rtcEngineConnectionDidLost` callback is triggered when the connection to the server is lost for more than 10 seconds, irrespective of channel participation.
 *
 * If the SDK is unable to rejoin the channel within 20 minutes after disconnection from BBRtc's edge server, it will cease attempts to reconnect.
 *
 * @param engine The BBRtcEngineKit object that manages the connection to the server.
 */

// Note: Since this callback has been deprecated, developers should now use the `rtcEngine:connectionChangedToState:reason:` callback to handle connection interruptions with the server.
- (void)rtcEngineConnectionDidInterrupted:(BBRtcEngineKit * _Nonnull)engine;

/**
 * Called when the connection is banned by the BBRtc server.
 *
 * **DEPRECATED** from v2.3.2. It is recommended to use the `connectionChangedToState` callback instead.
 *
 * This callback would have been triggered when your connection to the BBRtc server was actively banned, indicating a severe issue with the connection that requires immediate attention.
 *
 * @param engine The BBRtcEngineKit object that is affected by the server ban.
 */

// Note: Since this callback has been deprecated, developers should now use the `rtcEngine:connectionChangedToState:reason:` callback to handle scenarios where the connection is banned by the server.
- (void)rtcEngineConnectionDidBanned:(BBRtcEngineKit * _Nonnull)engine;

/**
 * Reports the audio quality of the remote user.
 *
 * **DEPRECATED** from v2.3.2. It is recommended to use the `remoteAudioStats` callback instead.
 *
 * This callback was triggered once every two seconds by the SDK to report the audio quality for each remote user or host transmitting an audio stream.
 * If a channel included multiple users or hosts sending audio streams, the SDK would trigger this callback separately for each one.
 *
 * @param engine  The BBRtcEngineKit object that manages audio streams.
 * @param uid     The user ID of the remote user whose audio quality is being reported.
 * @param quality The audio quality metric for the user. For details, refer to the BBRtcNetworkQuality documentation.
 * @param delay   The time delay in milliseconds of the audio packet from the sender to the receiver, encompassing delays from audio sampling pre-processing, transmission, and the jitter buffer.
 * @param lost    The packet loss rate in percentage of the audio packet from the sender to the receiver.
 */

// Note: Since this callback has been deprecated, developers should now use the `rtcEngine:remoteAudioStats:` callback to receive reports on the audio quality of remote users.
- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine audioQualityOfUid:(NSUInteger)uid quality:(BBRtcNetworkQuality)quality delay:(NSUInteger)delay lost:(NSUInteger)lost;

- (void)rtcEngine:(BBRtcEngineKit * _Nonnull)engine videoSizeChangedOfUid:(NSUInteger)uid size:(CGSize)size rotation:(NSInteger)rotation;

/**
 * Called when the camera turns on and is ready to capture video.
 *
 * **DEPRECATED** from v2.4.1. It is recommended to use the `BBRtcLocalVideoStreamStateCapturing(1)` state in the `state` parameter of the `localVideoStateChange` callback instead.
 *
 * This callback was triggered when the camera was successfully activated and prepared to capture video.
 *
 * @param engine The BBRtcEngineKit object that manages the camera and local video stream.
 */

// Note: Since this callback has been deprecated, developers should now monitor the `state` parameter in the `rtcEngine:localVideoStateChange:error:` callback for the `BBRtcLocalVideoStreamStateCapturing` state to determine camera readiness.
- (void)rtcEngineCameraDidReady:(BBRtcEngineKit * _Nonnull)engine;

/**
 * Called when the video playback stops.
 *
 * **DEPRECATED** from v2.4.1. It is recommended to use the `BBRtcLocalVideoStreamStateStopped(0)` state in the `state` parameter of the `localVideoStateChange` callback instead.
 *
 * This callback was triggered when the video playback ceased. The app could utilize this callback to adjust the view configuration, such as displaying alternative content in the view area.
 *
 * @param engine The BBRtcEngineKit object that manages video stream states.
 */

// Note: Since this callback has been deprecated, developers should now monitor the `state` parameter in the `rtcEngine:localVideoStateChange:error:` callback for the `BBRtcLocalVideoStreamStateStopped` state to handle the cessation of video playback.
- (void)rtcEngineVideoDidStop:(BBRtcEngineKit * _Nonnull)engine;

- (void)rtcEngineChorusStart:(BBRtcEngineKit * _Nonnull)engine;
- (void)rtcEngineChorusStop:(BBRtcEngineKit * _Nonnull)engine;
@end

#pragma mark - BBRtcEngineKit

/**
 * The BBRtcEngineKit class serves as the primary interface for utilizing the BBRtc SDK's capabilities.
 *
 * BBRtc ensures a high-quality experience (QoE) for global voice and video communications over the Internet.
 * It operates through a virtual global network that is specifically optimized for real-time communication in web and mobile applications.
 *
 * As the fundamental interface class of the BBRtc SDK, BBRtcEngineKit provides the necessary methods for voice and video communication.
 * By creating an instance of BBRtcEngineKit and invoking its methods, your app can leverage the full suite of SDK functionalities.
 */
__attribute__((visibility("default"))) @interface BBRtcEngineKit : NSObject

#pragma mark Core Service

/**-----------------------------------------------------------------------------
 * @name Core Service
 * -----------------------------------------------------------------------------
 */

/**
 * Initializes the BBRtcEngineKit object, which is essential for using the BBRtc communication services.
 *
 * You must call this method to set up the BBRtcEngineKit before utilizing any of its functionalities.
 * 
 * @note It is crucial to invoke this method prior to using any other BBRtc API.
 * @warning Communication is restricted to users with the same App ID.
 * @warning A single BBRtcEngineKit instance can only be associated with one App ID. If you need to switch App IDs, you must first call the `destroy` method to release the current instance. Then, reinitialize the BBRtcEngineKit with the new App ID.
 *
 * @param appId    The unique App ID provided by BBRtc. This is required to access the BBRtc Global Network for voice, video, and live-broadcast sessions. Apply for an App ID from the BBRtc portal if it is not included in your development kit.
 * @param delegate The BBRtcEngineDelegate object that will handle SDK event callbacks.
 *
 * @return An instance of the BBRtcEngineKit class, ready for method invocation.
 */

// Note: The `destroy` method and `joinChannelByToken` are part of the BBRtcEngineKit API, used for releasing resources and joining communication channels, respectively.
+ (instancetype _Nonnull)sharedEngineWithAppId:(NSString * _Nonnull)appId
                                      delegate:(id<BBRtcEngineDelegate> _Nullable)delegate;

/**
 * Destroys the RtcEngine instance and releases all resources used by the SDK.
 *
 * This method is recommended for applications that make occasional voice or video calls, allowing you to free up resources when not actively engaged in communications.
 *
 * Once this method is called to destroy the RtcEngine instance, no further SDK methods can be invoked, and no additional callbacks will be triggered. To resume communications, you must reinitialize the BBRtcEngineKit by calling `sharedEngineWithAppId:delegate:`.
 *
 * **Note:**
 * - Execute this method in a subthread to avoid blocking the main thread.
 * - This method is synchronous; it only returns after all BBRtcEngineKit resources have been released. Do not call this method within an SDK-generated callback, as doing so could cause a deadlock by requiring the callback to complete before the resources can be reclaimed.
 */

// Note: The `sharedEngineWithAppId:delegate:` method is part of the BBRtcEngineKit API for initializing a new instance of the BBRtcEngineKit.
+ (void)destroy;

+ (void)setRtcServerAddress:(NSString* _Nonnull)addr;

/**
 * Sets the channel profile for the BBRtcEngineKit, which determines the optimization algorithms applied by the SDK.
 *
 * The BBRtcEngineKit offers different channel profiles to cater to various communication needs:
 * - For video calls, it emphasizes smoothness and low latency.
 * - For video broadcasts, it prioritizes high video quality.
 *
 * **Note:**
 * - For consistent real-time communication quality, it is recommended that all users within a channel use the same channel profile.
 * - This method must be called before joining a channel with `joinChannelByToken`. Once a channel is joined, the channel profile cannot be changed.
 *
 * @param profile The channel profile to be set for the BBRtcEngineKit. For available profiles, refer to the BBRtcChannelProfile documentation.
 *
 * @return
 * - 0: Indicates success.
 * - A negative value: Indicates failure.
 */

// Note: The `joinChannelByToken` method and `BBRtcChannelProfile` are part of the BBRtcEngineKit API, used for joining channels and setting channel profiles, respectively.
- (int)setChannelProfile:(BBRtcChannelProfile)profile;

/**
 * Sets the role of a user in a Live-broadcast channel.
 *
 * This method is only applicable to the Live-broadcast profile and is used to define the user's role as either a host or an audience member (default) before joining a channel.
 * It can also be utilized to change a user's role after they have already joined the channel.
 *
 * After a user's role is successfully changed, the SDK triggers specific callbacks:
 * - On the local client: `rtcEngine:didClientRoleChanged:newRole:` to indicate the local user's role change.
 * - On remote clients: `rtcEngine:didJoinedOfUid:elapsed:` when a user becomes a host, or `rtcEngine:didOfflineOfUid:reason:` with `BBRtcUserOfflineReasonBecomeAudience` when a host steps down to an audience role.
 *
 * @param role The role to be assigned to the user. For available roles, refer to the BBRtcClientRole enumeration.
 *
 * @return
 * - 0: Indicates the operation was successful.
 * - A negative value: Indicates the operation failed.
 */

// Note: The specific callback methods mentioned are part of the BBRtcEngineDelegate protocol and are used to notify the app of changes in user roles within a Live-broadcast channel.
- (int)setClientRole:(BBRtcClientRole)role;

- (int)setChorusRole:(BBRtcChorusRole)role;

- (int)getChorusPosition;

/**
 * Joins a channel with a user ID, enabling communication with other users in the same channel.
 *
 * Users in the same channel can engage in group chats. However, users with different App IDs cannot communicate with each other, even if they join the same channel.
 *
 * To switch channels, you must call the `leaveChannel` method to exit the current call before entering another.
 * This method is asynchronous and can be called from the main user interface thread.
 *
 * The SDK uses iOS's AVAudioSession for audio recording and playback, which may affect the SDK's audio functionalities.
 *
 * If the `joinChannelByToken` method succeeds, the SDK triggers the `joinSuccessBlock`. If both `joinSuccessBlock` and `didJoinChannel` are implemented, `joinSuccessBlock` takes precedence.
 *
 * It is recommended to set `joinSuccessBlock` to nil to use the `didJoinChannel` delegate callback instead.
 *
 * A successful joinChannel method call triggers the following callbacks:
 * - On the local client: `didJoinChannel`
 * - On the remote client: `didJoinedOfUid` (if the user is in the Communication profile or is a BROADCASTER in the Live Broadcast profile)
 *
 * If the connection to BBRtc's server is interrupted due to poor network conditions, the SDK attempts to reconnect. Upon successful reconnection, the SDK triggers the `didRejoinChannel` callback on the local client.
 *
 * **Note:**
 * - Duplicate UIDs are not allowed in a channel. Ensure each device has a unique `uid` when joining the same channel.
 * - When joining a channel, the SDK sets the `AVAudioSession` category to `PlayAndRecord`, which may interrupt the sound played (e.g., ringtones). Do not set the `AVAudioSession` to any other mode.
 *
 * @param token A token generated by the app server. Use a static App ID for most cases, but use a token for enhanced security.
 *   - If using a static App ID, `token` can be nil.
 *   - If using a token, ensure it is generated based on the algorithm and App Certificate provided by BBRtc for user authentication.
 *   - The App ID used to create the token must match the App ID used to initialize the RTC engine with `sharedEngineWithAppId:delegate:`.
 * @param channelId A unique channel name for the BBRtc session, with a maximum length of 64 bytes. Valid characters include:
 *   - Lowercase and uppercase English letters
 *   - Numbers 0-9
 *   - Space, and special characters: "!#$%&()+-:;<=>?@[\\]^_{|}~,"
 * @param info Optional additional information about the channel. This information is not transmitted to other users.
 * @param uid The user ID, a unique 32-bit unsigned integer ranging from 1 to (2^32-1). If not assigned, the SDK will auto-assign and return a `uid` in `joinSuccessBlock`. Record this `uid` as the SDK does not maintain it.
 * @param joinSuccessBlock Returns the result of joining the specified channel. If nil, the SDK triggers the `didJoinChannel` callback.
 *
 * @return
 * - 0: Success
 * - Negative values: Failure codes, including but not limited to:
 *   - `BBRtcErrorCodeInvalidArgument`(-2): Invalid argument
 *   - `BBRtcErrorCodeNotReady`(-3): Not ready
 *   - `BBRtcErrorCodeRefused`(-5): Call refused
 */

// Note: The specific callback methods and error codes mentioned are part of the BBRtcEngineDelegate protocol and BBRtc SDK, used for notifying the app of channel join events and errors.
- (int)joinChannelByToken:(NSString * _Nullable)token
                channelId:(NSString * _Nonnull)channelId
                     info:(NSString * _Nullable)info
                      uid:(NSUInteger)uid
              joinSuccess:(void(^ _Nullable)(NSString * _Nonnull channel, NSUInteger uid, NSInteger elapsed))joinSuccessBlock;
/**
 * Joins a channel with a user ID and configures the subscription to audio or video streams.
 *
 * @since v3.3.0
 *
 * Users in the same channel can communicate with each other and initiate group chats. Users with different App IDs cannot call each other, even if they join the same channel.
 *
 * To switch channels, call the `leaveChannel` method to exit the current call before entering another.
 * This method is asynchronous and can be called from the main user interface thread.
 *
 * A successful `joinChannelByToken` call triggers the following callbacks:
 * - On the local client: `didJoinChannel`
 * - On the remote client: `didJoinedOfUid` (if the user is in the Communication profile or is a host in the Live Broadcast profile)
 *
 * If the connection to the BBRtc server is interrupted due to poor network conditions, the SDK attempts to reconnect. Upon successful reconnection, the SDK triggers the `didRejoinChannel` callback on the local client.
 *
 * **Note:**
 * - This method includes the `options` parameter to configure whether the user automatically subscribes to all remote audio and video streams in the channel upon joining. By default, the user subscribes to the audio and video streams of all other users in the channel.
 * - Ensure the App ID used for generating the token matches the App ID used in the `sharedEngineWithAppId:delegate:` method for initializing the BBRtcEngineKit object.
 *
 * @param token The token generated at your server. For details, see the documentation on token generation.
 * @param channelId The unique channel name for the BBRtc session in string format, with a maximum length of 64 bytes. Valid characters include lowercase and uppercase English letters, numeric characters, space, and various punctuation characters and symbols.
 * @param info (Optional) Additional information about the channel. This information is not transmitted to other users.
 * @param uid (Optional) User ID. A 32-bit unsigned integer unique within the channel. If not assigned, the SDK assigns and returns a `uid` in the `didJoinChannel` callback. Record this `uid` as the SDK does not maintain it.
 * @param options The channel media options: BBRtcChannelMediaOptions, which configure the subscription behavior for remote audio and video streams.
 *
 * @return
 * - `0` (`BBRtmpStreamingErrorCodeOK`): Success
 * - Negative values: Failure codes, including but not limited to:
 *   - `-2` (`BBRtcErrorCodeInvalidArgument`): Invalid parameter
 *   - `-3` (`BBRtcErrorCodeNotReady`): SDK not initialized
 *   - `-5` (`BBRtcErrorCodeRefused`): Request rejected, possibly due to conflicts with existing channels or streams
 *   - `-7` (`BBRtcErrorCodeNotInitialized`): SDK not initialized before calling this method
 */

// Note: The specific callback methods, error codes, and enumerations mentioned are part of the BBRtcEngineDelegate protocol and BBRtc SDK.
- (int)joinChannelByToken:(NSString* _Nullable)token channelId:(NSString* _Nonnull)channelId info:(NSString* _Nullable)info uid:(NSUInteger)uid options:(BBRtcChannelMediaOptions* _Nonnull)options;

/**
 * Switches to a different channel in a Live-broadcast session.
 *
 * This method enables the audience of a Live-broadcast channel to switch to another channel seamlessly.
 *
 * Upon successful channel switch, the following callbacks are triggered:
 * - `didLeaveChannelWithStats`: Indicates the user has left the original channel.
 * - `didJoinChannel`: Indicates the user has joined a new channel.
 *
 * @param token The token for authentication, which can be generated based on your security requirements:
 *   - For environments with low-security requirements, use the temporary token provided in the BBRtc Console. For more information, refer to the [temporary token documentation](https://docs.BBRtc.io/en/BBRtc%20Platform/token?platform=All%20Platforms#get-a-temporary-token).
 *   - For environments with high-security requirements, generate a token on your server. For more information, refer to the [token generation documentation](https://docs.BBRtc.io/en/BBRtc%20Platform/token?platform=All%20Platforms#get-a-token).
 * @param channelId The unique channel name for the BBRtc session, specified as a string with a maximum length of 64 bytes. Valid characters include lowercase and uppercase English letters, numbers, space, and various punctuation and symbols.
 * @param joinSuccessBlock A block that returns the result of joining the specified channel. If set to nil, the SDK will trigger the `didJoinChannel` callback instead.
 *
 * @note This method is intended for use by audience members in a Live-broadcast channel.
 *
 * @return
 * - `0`: Operation was successful.
 * - Negative values: Operation failed. Common error codes include:
 *   - `-2`: Invalid argument.
 *   - `-5`: The request was refused, possibly due to channel conflicts or other issues.
 */

// Note: If you are experiencing issues with accessing the documentation links, please ensure the URLs are correct and accessible. If problems persist, consider reaching out to BBRtc support for assistance.
- (int)switchChannelByToken:(NSString * _Nullable)token
                  channelId:(NSString * _Nonnull)channelId
                joinSuccess:(void(^ _Nullable)(NSString * _Nonnull channel, NSUInteger uid, NSInteger elapsed))joinSuccessBlock;

/**
 * Allows a user to leave a channel, effectively ending their call or session.
 *
 * Users must call the `leaveChannel` method to hang up or exit a call before they can join another channel.
 * Upon successfully leaving the channel and releasing all related resources, this method returns 0.
 * Note that this method is asynchronous; the user has not necessarily exited the channel when the method returns.
 *
 * A successful call to `leaveChannel` triggers the following callbacks:
 * - On the local client: `didLeaveChannelWithStats` to provide statistics of the call.
 * - On the remote client: `didOfflineOfUid` with `BBRtcUserOfflineReasonBecomeAudience` as the reason, if the user leaving is in a Communication channel or is a BROADCASTER in the Live Broadcast profile.
 *
 * **Note:**
 * - If `destroy` is called immediately after `leaveChannel`, the leaving process is interrupted, and the `didLeaveChannelWithStats` callback is not triggered.
 * - During CDN live streaming, calling this method triggers the `removePublishStreamUrl` method.
 * - By default, the SDK deactivates the audio session on iOS, which may affect other apps. To prevent this, use `setAudioSessionOperationRestriction` with `BBRtcAudioSessionOperationRestrictionDeactivateSession` so that the audio session remains active when `leaveChannel` is called.
 *
 * @param leaveChannelBlock A callback that indicates the user has left the channel and provides call statistics. For details, refer to BBRtcChannelStats.
 *
 * @return
 * - `0`: Success, indicating the user has successfully left the channel.
 * - A negative value: Failure, with specific error codes indicating the reason for the failure.
 */

// Note: Ensure to handle the asynchronous nature of leaving a channel and be prepared to manage related callbacks and error codes.
- (int)leaveChannel:(void(^ _Nullable)(BBRtcChannelStats * _Nonnull stat))leaveChannelBlock;
- (int)leaveChannel2:(void(^ _Nullable)(BBRtcChannelStats * _Nonnull stat))leaveChannelBlock;

/**
 * Retrieves a new token when the current token is set to expire.
 *
 * Once the token schema is enabled, the current token will expire after a set period, and a new token must be obtained. This situation arises when:
 * - The SDK triggers the `tokenPrivilegeWillExpire` callback, indicating that the token will soon expire.
 * - The `connectionChangedToState` callback reports a reason of `BBRtcConnectionChangedTokenExpired(9)`, indicating the token has expired.
 *
 * **Note:**
 * BBRtc recommends handling token expiration by using the `rtcEngineRequestToken` callback to report the `BBRtcErrorCodeTokenExpired(-109)` error. This is the preferred approach over using the `didOccurError` callback.
 *
 * It is crucial for the app to call this method to fetch a new token. Neglecting to update the token in a timely manner will cause the SDK to disconnect from the server.
 *
 * @param token The new token string retrieved from your server.
 *
 * @return
 * - `0`: Indicates the operation was successful, and the token has been refreshed.
 * - A negative value: Indicates a failure to refresh the token, with specific error codes providing further details on the failure.
 */

// Note: Always ensure that the token is obtained securely from your server to maintain the integrity and security of the authentication process.
- (int)renewToken:(NSString * _Nonnull)token;

/** Gets the connection state of the app.

@return The connection state, see [BBRtcConnectionStateType](BBRtcConnectionStateType).
*/
- (BBRtcConnectionStateType)getConnectionState;

/**
 * Initiates the relay of media streams between channels.
 *
 * Upon successful execution, the SDK triggers the `channelMediaRelayStateDidChange` and `didReceiveChannelMediaRelayEvent` callbacks to report the state and events of the media stream relay process.
 *
 * - If the `channelMediaRelayStateDidChange` callback returns `BBRtcChannelMediaRelayStateRunning(2)` and `BBRtcChannelMediaRelayStateIdle(0)`, and the `didReceiveChannelMediaRelayEvent` callback returns `BBRtcChannelMediaRelayEventSentToDestinationChannel(4)`, it indicates that the SDK has started relaying media streams to the specified destination channel.
 * - If the `channelMediaRelayStateDidChange` callback returns `BBRtcChannelMediaRelayStateFailure(3)`, an error has occurred in the media stream relay process.
 *
 * **Notes:**
 * - This method should be called after joining the channel with the `joinChannel` method.
 * - The method is only effective when you are in the broadcaster role within a Live-broadcast channel.
 * - To initiate another relay after a successful call, ensure you first call the `stopChannelMediaRelay` method to terminate the current relay.
 * - Contact sales-us@BBRtc.io for assistance before implementing this functionality.
 * - This API does not support string user accounts.
 *
 * @param config The configuration settings for the media stream relay, as defined by `BBRtcChannelMediaRelayConfiguration`.
 *
 * @return
 * - `0`: Indicates the operation was successful and the media stream relay has started or is about to start.
 * - A negative value: Indicates a failure to start the media stream relay, with specific error codes providing further details on the failure.
 */

// Note: Ensure to follow the correct sequence of calls and configurations when implementing media stream relay functionality.
- (int)startChannelMediaRelay:(BBRtcChannelMediaRelayConfiguration * _Nonnull)config;

/**
 * Updates the destination channels for an ongoing media stream relay.
 *
 * Once the channel media relay has been initiated, should you wish to extend the media stream relay to additional channels or exit the current relay channel, you may invoke the `updateChannelMediaRelay` method.
 *
 * Upon a successful method call, the SDK will trigger the `didReceiveChannelMediaRelayEvent` callback with the `BBRtcChannelMediaRelayEventUpdateDestinationChannel(7)` state code, indicating the update has been acknowledged.
 *
 * **Note:**
 * - This method should be called subsequent to the `startChannelMediaRelay` method to modify the relay configuration.
 * - The method supports the addition of up to four destination channels within the relay. If the relay already encompasses four destination channels, utilize the `removeDestinationInfoForChannelName` method within `channelMediaRelayConfiguration` to eliminate superfluous channels prior to invoking this method.
 *
 * @param config The configuration object detailing the media stream relay's new setup, as defined by `BBRtcChannelMediaRelayConfiguration`.
 *
 * @return
 * - `0`: Indicates the operation was successful and the destination channels for the media stream relay have been updated.
 * - A negative value: Indicates a failure to update the media stream relay, with specific error codes providing further details on the failure.
 */

// Note: Ensure proper configuration management when updating the media stream relay to maintain the intended relay structure and avoid exceeding the supported number of destination channels.
- (int)updateChannelMediaRelay:(BBRtcChannelMediaRelayConfiguration * _Nonnull)config;

/**
 * Stops the media stream relay.
 *
 * Once the relay is stopped, the broadcaster exits from all destination channels.
 * A successful execution of this method triggers the `channelMediaRelayStateDidChange` callback.
 * If the callback returns `BBRtcChannelMediaRelayStateIdle(0)` and `BBRtcChannelMediaRelayErrorNone(0)`, it indicates that the broadcaster has successfully ceased the relay.
 *
 * @note If the method call fails, the SDK triggers the `channelMediaRelayStateDidChange` callback with error states such as `BBRtcChannelMediaRelayErrorServerNoResponse(2)` or `BBRtcChannelMediaRelayEventUpdateDestinationChannelRefused(8)`.
 * In such cases, you can forcibly leave the channel by invoking the `leaveChannel` method, which will also terminate the media stream relay.
 *
 * @return
 * - `0`: Indicates the operation was successful and the media stream relay has been stopped.
 * - A negative value: Indicates a failure to stop the media stream relay, with specific error codes detailing the reason for the failure.
 */

// Note: Ensure to handle callback responses appropriately to determine the success or failure of stopping the media stream relay.
- (int)stopChannelMediaRelay;

#pragma mark Core Audio

/**-----------------------------------------------------------------------------
 * @name Core Audio
 * -----------------------------------------------------------------------------
 */

/**
 * Enables the audio module within the BBRtcEngineKit.
 *
 * By default, the audio module is enabled for functionality.
 *
 * **Note:**
 * - This method impacts the internal audio engine and can be invoked after the `leaveChannel` method. It is effective whether called before or after joining a channel.
 * - As this method resets the internal audio engine, it may take some time to become active. BBRtc recommends using the following separate API methods for finer control over the audio engine modules:
 *     - `enableLocalAudio`: Toggles the use of the microphone to capture the local audio stream.
 *     - `muteLocalAudioStream`: Controls the publishing of the local audio stream.
 *     - `muteRemoteAudioStream`: Determines whether to subscribe to and play a specific remote audio stream.
 *     - `muteAllRemoteAudioStreams`: Manages subscription to and playback of all remote audio streams.
 *
 * @return
 * - `0`: Indicates the method call was successful and the audio module is enabled.
 * - A negative value: Indicates a failure in enabling the audio module, with specific error codes providing further details.
 */

// Note: When managing audio functionality, consider the timing and sequence of method calls to ensure the desired audio settings are applied effectively.
- (int)enableAudio;

/**
 * Disables the audio module within the BBRtcEngineKit.
 *
 * **Note:**
 * - This method impacts the internal audio engine and can be invoked after the `leaveChannel` method. It is effective whether called before or after joining a channel.
 * - As this method resets the internal audio engine, it may take some time to become active. BBRtc recommends using the following separate API methods for finer control over the audio engine modules:
 *     - `enableLocalAudio`: Controls the activation of the microphone for capturing the local audio stream.
 *     - `muteLocalAudioStream`: Manages the publishing of the local audio stream.
 *     - `muteRemoteAudioStream`: Determines whether to subscribe to and play a specific remote audio stream.
 *     - `muteAllRemoteAudioStreams`: Toggles the subscription to and playback of all remote audio streams.
 *
 * @return
 * - `0`: Indicates the method call was successful and the audio module has been disabled.
 * - A negative value: Indicates a failure in disabling the audio module, with specific error codes providing further details.
 */

// Note: When adjusting audio settings, consider the timing and sequence of method calls to ensure the audio module is controlled as intended.
- (int)disableAudio;

/**
 * Configures the audio parameters and application scenarios for optimal audio settings.
 *
 * **Note:**
 * - This method must be called before joining the channel with the `joinChannelByToken` method.
 * - In the Communication profile, you can only set the profile, not the scenario.
 * - In both Communication and Live-broadcast profiles, the actual bitrates may vary from your settings due to the network's self-adaptation capabilities.
 * - For scenarios that demand high-quality audio, such as music education, it is recommended to set the `profile` to `BBRtcAudioProfileMusicHighQuality(4)` and the `scenario` to `BBRtcAudioScenarioGameStreaming(3)`.
 *
 * @param profile Sets the audio profile which determines the sample rate, bitrate, encoding mode, and channel count. For available profiles, refer to BBRtcAudioProfile.
 * @param scenario Sets the audio application scenario which influences the device's volume tracks, choosing between in-call volume and media volume. For available scenarios, refer to BBRtcAudioScenario. For more information on the distinction between in-call volume and media volume, see the BBRtc documentation.
 *
 * @return
 * - `0`: Indicates the method call was successful and the audio settings have been configured.
 * - A negative value: Indicates a failure to set the audio parameters, with specific error codes providing further details.
 */

// Note: Ensure to configure the audio profile and scenario according to your application's needs and the expected audio quality before joining a channel.
- (int)setAudioProfile:(BBRtcAudioProfile)profile
              scenario:(BBRtcAudioScenario)scenario;

/** Adjusts the recording volume.

 @param volume Recording volume. The value ranges between 0 and 400:

 * 0: Mute.
 * 100: Original volume.
 * 400: (Maximum) Four times the original volume with signal clipping protection.

 @return * 0: Success.
* < 0: Failure.
 */
- (int)adjustRecordingSignalVolume:(NSInteger)volume;

/** Adjusts the playback volume of all remote users.
 
 **Note**

 - This method adjusts the playback volume which is mixed volume of all remote users.
 - Since v2.3.2, to mute the local audio playback, call both `adjustPlaybackSignalVolume` and [adjustAudioMixingVolume]([BBRtcEngineKit adjustAudioMixingVolume:]), and set `volume` as 0.

 @param volume The playback volume of all remote users. The value ranges from 0 to 400:

 * 0: Mute.
 * 100: Original volume.
 * 400: (Maximum) Four times the original volume with signal clipping protection.

 @return * 0: Success.
 * < 0: Failure.
 */
- (int)adjustPlaybackSignalVolume:(NSInteger)volume;

/**
 * Enables the SDK to periodically report to the app information about which users are speaking and the volume levels of the speakers.
 *
 * @param interval Sets the time interval between consecutive volume indications:
 *      - Less than or equal to 0: Disables the volume indication.
 *      - Greater than 0: Specifies the time interval in milliseconds between consecutive volume indications. BBRtc recommends an interval of 200 ms or more. Once enabled, the SDK issues volume indications at the set interval in the `reportAudioVolumeIndicationOfSpeakers` and `audioVolumeIndicationBlock` callbacks, irrespective of speaking activity in the channel.
 * @param smooth The smoothing factor that determines the sensitivity of the audio volume indicator, ranging from 0 to 10. A higher value indicates greater sensitivity. The recommended value is 3.
 * @param report_vad Enables or disables voice activity detection for the local user:
 *      - YES: Enables voice activity detection. When enabled, the `vad` parameter in the `reportAudioVolumeIndicationOfSpeakers` callback provides the voice activity status of the local user.
 *      - NO: (Default) Disables voice activity detection. When disabled, the `vad` parameter does not report the voice activity status of the local user, except in scenarios where the engine automatically detects the local user's voice activity.
 *
 * @return
 * - `0`: Indicates the method call was successful and the volume indication settings have been applied.
 * - A negative value: Indicates a failure to set the volume indication parameters, with specific error codes providing further details.
 */

// Note: Properly configure the volume indication interval, smoothing factor, and voice activity detection to optimize the audio feedback for your application's needs.
- (int)enableAudioVolumeIndication:(NSInteger)interval
                            smooth:(NSInteger)smooth
                        report_vad:(BOOL)report_vad;

/**
 * Enables or disables local audio capture.
 *
 * When an app joins a channel, the audio module is enabled by default. This method allows you to disable or re-enable local audio capture, effectively controlling the local audio recording and processing.
 * Disabling local audio capture does not affect the reception or playback of remote audio streams. Use `enableLocalAudio(NO)` in scenarios where a user intends to receive remote audio without sending any audio to other channel participants.
 *
 * The SDK triggers the `didMicrophoneEnabled` callback once the local audio module is disabled or re-enabled.
 *
 * **Note:**
 * - Call this method after the `joinChannelByToken` method.
 * - This method differs from `muteLocalAudioStream`:
 *   - `enableLocalAudio`: Disables or re-enables local audio capture and processing. Disabling or re-enabling local recording may cause a pause in the playback of remote audio for the local user.
 *   - `muteLocalAudioStream`: Controls the sending of the local audio stream, allowing you to mute or unmute the transmission to other users in the channel.
 *
 * @param enabled YES to enable the local audio module for capturing and processing local audio; NO to disable it.
 * @return
 * - `0`: Indicates the method call was successful and the local audio module is now enabled or disabled as specified.
 * - A negative value: Indicates a failure to change the local audio module state, with specific error codes providing further details.
 */

// Note: Consider the user's intended audio experience and the app's functionality when deciding to enable or disable local audio capture.
- (int)enableLocalAudio:(BOOL)enabled;

/**
 * Controls the transmission of the local audio stream.
 *
 * This method is used to start or stop sending the local audio stream to other users in the channel.
 * When `muteLocalAudioStream` is successfully called, it triggers the `didAudioMuted` callback on the remote client, indicating whether the local audio is being muted or unmuted.
 *
 * **Note:**
 * - Setting `mute` to `YES` does not disable the microphone; it only stops the transmission of the local audio stream. It does not impact any ongoing local audio recording.
 * - If you call `setChannelProfile` after using this method, the SDK may reset the mute state of the local audio based on the new channel profile and user role. Therefore, it is recommended to call `muteLocalAudioStream` after `setChannelProfile`.
 *
 * @param mute Determines whether to stop or start sending the local audio stream:
 *      - YES: Stops sending the local audio stream.
 *      - NO: (Default) Continues sending the local audio stream.
 *
 * @return
 * - `0`: Indicates the method call was successful and the transmission of the local audio stream has been controlled as specified.
 * - A negative value: Indicates a failure to control the transmission of the local audio stream, with specific error codes providing further details.
 */

// Note: Use this method to manage the flow of the local audio stream within the channel according to the user's role and the channel's profile settings.
- (int)muteLocalAudioStream:(BOOL)mute;

/**
 * Controls the reception of a specified remote user's audio stream.
 *
 * Use this method to start or stop receiving the audio stream from a specific remote user in the channel.
 *
 * **Note:**
 * - If you have previously called the `muteAllRemoteAudioStreams` method with `mute` set to `YES` to mute all remote audio streams, you must first call `muteAllRemoteAudioStreams` again with `mute` set to `NO` to unmute all streams. This should be done before calling this method to control the reception of a specific user's audio stream. The `muteAllRemoteAudioStreams` method affects all remote audio streams, whereas the `muteRemoteAudioStream` method targets an individual stream.
 *
 * @param uid  The user ID of the specified remote user whose audio stream you want to control.
 * @param mute Determines whether to stop or start receiving the audio stream from the specified remote user:
 *      - YES: Stops receiving the audio stream from the specified remote user.
 *      - NO: (Default) Continues receiving the audio stream from the specified remote user.
 *
 * @return
 * - `0`: Indicates the method call was successful and the reception of the specified remote user's audio stream has been controlled as specified.
 * - A negative value: Indicates a failure to control the reception of the audio stream, with specific error codes providing further details.
 */

// Note: Properly manage the muting of all remote audio streams before adjusting the settings for individual users to ensure accurate audio stream reception.
- (int)muteRemoteAudioStream:(NSUInteger)uid mute:(BOOL)mute;

/**
 * Controls the reception of all remote audio streams in the channel.
 *
 * This method enables or disables the reception of audio streams from all remote users in the channel.
 *
 * @param mute Determines the audio stream reception setting:
 *      - YES: Stops receiving all remote audio streams, effectively muting all incoming audio from other users.
 *      - NO: (Default) Receives all remote audio streams, allowing the audio from all users to be heard.
 *
 * @return
 * - `0`: Indicates the method call was successful and the reception of remote audio streams has been set as specified.
 * - A negative value: Indicates a failure to set the audio reception state, with specific error codes providing further details.
 */
- (int)muteAllRemoteAudioStreams:(BOOL)mute;

/**
 * Sets the default behavior for receiving all remote audio streams.
 *
 * This method establishes whether to receive audio streams from all remote users by default. It can be called either before or after joining a channel. If called after joining a channel, it will not affect the audio streams of users who have already joined.
 *
 * @param mute Determines the default setting for receiving remote audio streams:
 *      - YES: Prevents receiving audio streams from all remote users by default.
 *      - NO: (Default) Allows receiving audio streams from all remote users by default.
 *
 * @return
 * - `0`: Indicates the method call was successful and the default reception of remote audio streams has been set as specified.
 * - A negative value: Indicates a failure to set the default audio reception state, with specific error codes providing further details.
 */

// Note: This method is useful for managing the initial reception of audio streams when users join the channel, and can be adjusted according to the application's audio management strategy.
- (int)setDefaultMuteAllRemoteAudioStreams:(BOOL)mute;

/**
 * Adjusts the playback volume for a specified remote user.
 *
 * **Since** v3.0.0.
 *
 * This method can be invoked multiple times to modify the playback volume for various remote users or to make multiple adjustments for the same remote user.
 *
 * **Note:**
 * - This method should be called after joining a channel.
 * - The playback volume mentioned here is the mixed volume for a specified remote user.
 * - This method is capable of adjusting the playback volume for only one specified remote user at a time. To adjust the playback volume for different remote users, you must call this method separately for each user.
 *
 * @param uid The user ID of the remote user whose playback volume is to be adjusted.
 * @param volume The playback volume level for the specified remote user, with a range from 0 to 100:
 *      - 0: Mute the audio.
 *      - 100: Play at the original volume.
 *
 * @return
 * - `0`: Indicates the method call was successful and the playback volume has been adjusted as specified.
 * - A negative value: Indicates a failure to adjust the playback volume, with specific error codes providing further details.
 */

// Note: Use this method to fine-tune the audio experience by controlling the playback volume of individual remote users in the channel.
- (int)adjustUserPlaybackSignalVolume:(NSUInteger)uid volume:(int)volume;


#pragma mark Core Video

/**-----------------------------------------------------------------------------
 * @name Core Video
 * -----------------------------------------------------------------------------
 */

/**
 * Enables the video module for the BBRtcEngineKit.
 *
 * You can invoke this method either before joining a channel or while you are already in a call. Calling this method before entering a channel initializes the service in video mode. During an audio call, calling this method switches the mode from audio to video.
 *
 * A successful call to `enableVideo` triggers the `didVideoEnabled(YES)` callback on the remote client, indicating that video has been enabled.
 *
 * To disable the video, use the `disableVideo` method.
 *
 * **Note:**
 * - This method impacts the internal engine and can be called after the `leaveChannel` method.
 * - As this method resets the internal engine, it may take some time to become effective. BBRtc recommends using the following separate API methods for finer control over the video engine modules:
 *     - `enableLocalVideo`: Controls whether the camera is enabled to create the local video stream.
 *     - `muteLocalVideoStream`: Determines whether the local video stream is published.
 *     - `muteRemoteVideoStream`: Manages whether to subscribe to and play a specific remote video stream.
 *     - `muteAllRemoteVideoStreams`: Toggles the subscription to and playback of all remote video streams.
 *
 * @return
 * - `0`: Indicates the method call was successful and the video module has been enabled.
 * - A negative value: Indicates a failure to enable the video module, with specific error codes providing further details.
 */

// Note: Properly manage the enabling and disabling of the video module according to the user's needs and the application's functionality within the call.
- (int)enableVideo;

/**
 * Disables the video module for the BBRtcEngineKit.
 *
 * You may invoke this method either before joining a channel or while you are in a call. Calling this method before entering a channel initializes the service in audio mode. During a video call, this method switches the mode from video to audio.
 *
 * To enable the video module, call the `enableVideo` method.
 *
 * A successful call to `disableVideo` triggers the `didVideoEnabled(NO)` callback on the remote client, signaling that video has been disabled.
 *
 * **Note:**
 * - This method influences the internal engine and can be called after the `leaveChannel` method.
 * - Since this method resets the internal engine, it may take some time to become effective. BBRtc recommends using the following separate API methods for finer control over the video engine modules:
 *     - `enableLocalVideo`: Controls the activation of the camera to capture the local video stream.
 *     - `muteLocalVideoStream`: Manages the publishing of the local video stream.
 *     - `muteRemoteVideoStream`: Determines whether to subscribe to and play a specific remote video stream.
 *     - `muteAllRemoteVideoStreams`: Toggles the subscription to and playback of all remote video streams.
 *
 * @return
 * - `0`: Indicates the method call was successful and the video module has been disabled.
 * - A negative value: Indicates a failure to disable the video module, with specific error codes providing further details.
 */

// Note: Use this method to control the video functionality according to the user's needs and the application's requirements during a call.
- (int)disableVideo;

/**
 * Configures the video encoder settings.
 *
 * The video encoder configuration determines a set of video parameters such as resolution, frame rate, bitrate, and video orientation.
 * The parameters defined by this method represent the maximum values intended for ideal network conditions. In cases where the network conditions are not reliable, the video engine will attempt to use lower settings down the list until a successful configuration is achieved.
 *
 * If there is no need to adjust the video encoder configuration after joining a channel, this method can be called in advance of `enableVideo` to minimize the rendering time of the initial video frame.
 *
 * **Note:**
 * - From version 2.3.0, the following API methods have been deprecated:
 *     - `setVideoProfile:swapWidthAndHeight:`
 *     - `setVideoResolution:andFrameRate:bitrate:`
 *
 * @param config The video encoder configuration, defined by the BBRtcVideoEncoderConfiguration struct.
 * @return
 * - `0`: Indicates the method call was successful and the video encoder configuration has been set.
 * - A negative value: Indicates a failure to set the video encoder configuration, with specific error codes providing further details.
 */

// Note: Properly configure the video encoder settings to optimize video quality and performance based on the expected network conditions and application requirements.
- (int)setVideoEncoderConfiguration:(BBRtcVideoEncoderConfiguration * _Nonnull)config;

/**
 * Initializes the local video view on the local device.
 *
 * This method configures the video view for the local stream, which is only visible to the local user and does not affect the published local video stream.
 * It is used to bind the local video stream to a specific video view and to configure the rendering and mirror modes of the video output.
 * To detach the local video stream from a view, set the `view` property of BBRtcVideoCanvas to `nil`.
 *
 * **Note:**
 * - This method should be called before joining a channel.
 * - To change the rendering or mirror mode of the local video view while in a call, use the `setLocalRenderMode:mirrorMode:` method.
 *
 * @param local The configuration for the local video view, including the view and its settings. For details, refer to BBRtcVideoCanvas.
 *
 * @return
 * - `0`: Indicates the method call was successful and the local video view has been initialized.
 * - A negative value: Indicates a failure to initialize the local video view, with specific error codes providing further details.
 */

// Note: Properly initialize the local video view according to the application's UI requirements before starting the video session.
- (int)setupLocalVideo:(BBRtcVideoCanvas * _Nullable)local;

/**
 * Initializes the video view for a remote user on the local device.
 *
 * This method sets up the video view for a remote user's stream, which is only visible to the local user.
 * It is used to bind the remote video stream to a specific video view and to configure the rendering and mirror modes for the video display.
 *
 * The application should specify the `uid` of the remote video in this method call before the user joins a channel.
 * If the remote `uid` is not known in advance, it can be set after the application receives the `userJoinedBlock` callback.
 *
 * If the Video Recording function is enabled, the Video Recording Service joins the channel as a dummy client.
 * This can cause other clients to receive the `didJoinedOfUid` callback. Do not bind the dummy client to the app view,
 * as the dummy client does not send any video streams. If the dummy client is indistinguishable in your app,
 * consider binding the remote user to the view when the SDK triggers the `firstRemoteVideoDecodedOfUid` callback.
 *
 * To detach a remote user from the view, set the `view` property in BBRtcVideoCanvas to `nil`.
 * Once the remote user leaves the channel, the SDK automatically unbinds the remote user.
 *
 * **Note:**
 * - To update the rendering or mirror mode of the remote video view during a call, use the `setRemoteRenderMode:renderMode:mirrorMode:` method.
 *
 * @param remote The configuration for the remote video view, including the view and its settings. For details, refer to BBRtcVideoCanvas.
 *
 * @return
 * - `0`: Indicates the method call was successful and the remote video view has been initialized.
 * - A negative value: Indicates a failure to initialize the remote video view, with specific error codes providing further details.
 */

// Note: Ensure the proper initialization of the remote video view according to the user's `uid` and the application's UI requirements before starting the video session.
- (int)setupRemoteVideo:(BBRtcVideoCanvas * _Nonnull)remote;


/**
 * Updates the display mode of the local video view.
 *
 * **Since** v3.0.0.
 *
 * After the local video view has been initialized, this method can be used to modify its rendering and mirror modes.
 * It affects only the video view visible to the local user and does not impact the published local video stream.
 *
 * **Note:**
 * - Make sure to call `setupLocalVideo` to initialize the local video view before using this method.
 * - During an ongoing call, this method can be called multiple times to make updates to the display mode of the local video as needed.
 *
 * @param renderMode The rendering mode for the local video view, which determines how the video is scaled and positioned within the view. For available modes, refer to BBRtcVideoRenderMode.
 * @param mirrorMode The mirror mode for the local video view, which specifies whether the video is mirrored horizontally. For available modes, refer to BBRtcVideoMirrorMode.
 *
 * **Note:**
 * - By default, the SDK enables mirror mode when using a front camera and disables it when using a rear camera.
 *
 * @return
 * - `0`: Indicates the method call was successful and the display mode of the local video view has been updated.
 * - A negative value: Indicates a failure to update the display mode, with specific error codes providing further details.
 */

// Note: Adjust the local video view's display settings to enhance the user's experience during video calls.
- (int)setLocalRenderMode:(BBRtcVideoRenderMode) renderMode
               mirrorMode:(BBRtcVideoMirrorMode) mirrorMode;

/**
 * Sets the display mode for a remote user's video view.
 *
 * **Since** v3.0.0.
 *
 * Once the video view for a remote user has been initialized, this method can be used to update its rendering and mirror modes.
 * This method affects only the video view as seen by the local user and does not alter the video stream of the remote user.
 *
 * **Note:**
 * - Ensure that you have called `setupRemoteVideo` to initialize the remote video view before using this method.
 * - During an ongoing call, this method can be called multiple times to make updates to the display mode of the remote user's video view as needed.
 *
 * @param uid The user ID of the remote user whose video view display mode you want to update.
 * @param renderMode The rendering mode for the remote video view, which determines how the video is scaled and positioned within the view. For available modes, refer to BBRtcVideoRenderMode.
 * @param mirrorMode The mirror mode for the remote video view, which specifies whether the video is mirrored horizontally. For available modes, refer to BBRtcVideoMirrorMode.
 *
 * **Note:**
 * - The SDK disables the mirror mode by default.
 *
 * @return
 * - `0`: Indicates the method call was successful and the remote video view's display mode has been updated.
 * - A negative value: Indicates a failure to update the display mode, with specific error codes providing further details.
 */

// Note: Properly configure the remote video view's display settings to ensure the best viewing experience for the local user during video calls.
- (int)setRemoteRenderMode: (NSUInteger)uid
                renderMode:(BBRtcVideoRenderMode) renderMode
                mirrorMode:(BBRtcVideoMirrorMode) mirrorMode;

/**
 * Starts the local video preview before joining a channel.
 *
 * By default, the local video preview is displayed in mirror mode.
 * To start the local video preview, you must first:
 * - Call `setupLocalVideo` to set up the local preview window and configure its attributes.
 * - Call `enableVideo` to enable video capabilities.
 *
 * **Note:**
 * - Once the local video preview is started using this method, if you leave the channel by calling `leaveChannel`, the local video preview will continue until you explicitly call the `stopPreview` method to turn it off.
 *
 * @return
 * - `0`: Indicates the method call was successful and the local video preview has started.
 * - A negative value: Indicates a failure to start the local video preview, with specific error codes providing further details.
 */

// Note: Ensure that the local video is properly configured and enabled before starting the preview to avoid unexpected behavior.
- (int)startPreview;

/** Stops the local video preview and the video.

 @return * 0: Success.
* < 0: Failure.
 */
- (int)stopPreview;

/**
 * Disables or re-enables the local video capturer.
 *
 * This method controls the local video capturer, and does not affect the reception of remote video streams.
 * After enabling video with `enableVideo`, the local video capturer is active by default.
 * To disable the local video capturer, call `enableLocalVideo` with `NO`. To re-enable, call it with `YES`.
 *
 * Successfully disabling or re-enabling the local video capturer triggers the `didLocalVideoEnabled` callback on the remote client, indicating the change in the local video status.
 *
 * **Note:**
 * - This method affects the internal engine and can be called after the `leaveChannel` method has been called.
 *
 * @param enabled A boolean value that sets whether to enable or disable the local video, which includes the capturer, renderer, and sender:
 *      - YES: (Default) Enables the local video.
 *      - NO: Disables the local video, preventing remote users from receiving the video stream of this user, while still allowing this user to receive video streams from other remote users.
 *
 * @return
 * - `0`: Indicates the method call was successful and the local video has been enabled or disabled as specified.
 * - A negative value: Indicates a failure to change the local video state, with specific error codes providing further details.
 */

// Note: Use this method to manage the local video functionality according to the user's needs and the application's requirements during a call.

- (int)enableLocalVideo:(BOOL)enabled;


/**
 * Controls the transmission of the local video stream.
 *
 * This method allows you to start or stop sending the local video stream to other users in the channel.
 * A successful call to `muteLocalVideoStream` triggers the `didVideoMuted` callback on the remote client, indicating whether the local video is being muted or unmuted.
 *
 * **Note:**
 * - Setting `mute` to `YES` does not disable the camera; it only stops the transmission of the local video stream. This method is faster in taking effect compared to `enableLocalVideo`, which controls the capture and sending of the local video stream.
 * - If you call `setChannelProfile` after using this method, the SDK may reset the mute state of the local video based on the channel profile and user role. Therefore, it is recommended to call `muteLocalVideoStream` after `setChannelProfile`.
 *
 * @param mute A boolean value that determines whether to stop or start sending the local video stream:
 *      - YES: Stops sending the local video stream.
 *      - NO: (Default) Continues sending the local video stream.
 *
 * @return
 * - `0`: Indicates the method call was successful and the transmission of the local video stream has been controlled as specified.
 * - A negative value: Indicates a failure to control the transmission of the local video stream, with specific error codes providing further details.
 */

// Note: Use this method to manage the flow of the local video stream within the channel according to the user's role and the channel's profile settings.

- (int)muteLocalVideoStream:(BOOL)mute;

/**
 * Controls the reception of all remote video streams in the channel.
 *
 * This method allows you to start or stop receiving video streams from all remote users within a channel.
 *
 * @param mute A boolean value that determines the reception of remote video streams:
 *      - YES: Stops receiving all remote video streams, effectively muting all incoming video from other users.
 *      - NO: (Default) Receives all remote video streams, allowing the display of video from all users in the channel.
 *
 * @return
 * - `0`: Indicates the method call was successful and the reception of remote video streams has been set as specified.
 * - A negative value: Indicates a failure to set the reception of remote video streams, with specific error codes providing further details.
 */

// Note: Use this method to manage the overall reception of video streams from all remote users, according to the needs of your application and user experience requirements.
- (int)muteAllRemoteVideoStreams:(BOOL)mute;

/**
 * Controls the reception of a specified remote user's video stream.
 *
 * **Note:**
 * - If you have previously called the `muteAllRemoteVideoStreams` method with `mute` set to `YES` to stop receiving all remote video streams, you must call `muteAllRemoteVideoStreams` again with `mute` set to `NO` before using this method to control the reception of a specific user's video stream.
 *
 * @param uid  The user ID of the specified remote user whose video stream reception you wish to control.
 * @param mute A boolean value that determines whether to stop or start receiving the video stream from the specified remote user:
 *      - YES: Stops receiving the video stream from the specified remote user.
 *      - NO: (Default) Continues receiving the video stream from the specified remote user.
 *
 * @return
 * - `0`: Indicates the method call was successful and the reception of the specified remote user's video stream has been controlled as specified.
 * - A negative value: Indicates a failure to control the reception of the video stream, with specific error codes providing further details.
 */

// Note: Use this method to selectively receive or stop receiving video streams from individual remote users in the channel, based on your application's needs.
- (int)muteRemoteVideoStream:(NSUInteger)uid
                        mute:(BOOL)mute;

/**
 * Sets the default behavior for receiving remote video streams.
 *
 * This method establishes whether to receive video streams from all remote users by default.
 *
 * @param mute A boolean value that determines the default setting for receiving remote video streams:
 *      - YES: Stops receiving all remote video streams by default.
 *      - NO: (Default) Receives all remote video streams by default.
 *
 * @return
 * - `0`: Indicates the method call was successful and the default reception of remote video streams has been set as specified.
 * - A negative value: Indicates a failure to set the default reception of remote video streams, with specific error codes providing further details.
 */

// Note: This method is used to manage the initial reception of video streams from all remote users. Adjust the settings based on the application's requirements and user preferences.
- (int)setDefaultMuteAllRemoteVideoStreams:(BOOL)mute;


#pragma mark Video Pre-Process and Post-Process
/**
 * -------------------------------------------------------------------------------
 * @name Video Pre-Process and Post-Process
 * -----------------------------------------------------------------------------
 */

/**
 * Enables or disables image enhancement and sets the options. (iOS only)
 *
 * @note This method should be called after the `enableVideo` method.
 *
 * @param enable A boolean value that determines whether image enhancement is enabled:
 *      - `YES`: Image enhancement is enabled.
 *      - `NO`: Image enhancement is disabled.
 * @param options The image enhancement options. For details, refer to BBRtcBeautyOptions.
 *
 * @return
 * - `0`: Indicates the method call was successful and image enhancement has been enabled or disabled as specified.
 * - A negative value: Indicates a failure to set image enhancement options, with specific error codes providing further details.
 */

// Note: Use this method to adjust the visual quality of the video stream by enabling or disabling image enhancement features, available exclusively on iOS.
- (int)setBeautyEffectOptions:(BOOL)enable options:(BBRtcBeautyOptions * _Nullable)options;

#if TARGET_OS_IPHONE
- (int)enableRemoteSuperResolution:(NSUInteger)uid enabled:(BOOL)enabled;
#endif


#pragma mark Audio Routing Controller

/**-----------------------------------------------------------------------------
 * @name Audio Routing Controller
 * -----------------------------------------------------------------------------
 */

#if TARGET_OS_IPHONE
/**
 * Sets the default audio route for received audio. (iOS only)
 *
 * This method determines whether the received audio is directed to the earpiece or the speakerphone by default before joining a channel.
 * If this method is not called, the audio is directed to the earpiece by default.
 *
 * To change the default audio route after joining a channel, use the `setEnableSpeakerphone` method.
 *
 * **Note:**
 * - This method is effective only in audio mode.
 * - It should be called before the `joinChannel` method is invoked.
 *
 * The default audio routing for each mode is as follows:
 * - Voice: Earpiece.
 * - Video: Speakerphone. In the Communication profile, if a user calls the `disableVideo` method, or if a user calls both the `muteLocalVideoStream` and `muteAllRemoteVideoStreams` methods, the default audio route is automatically switched to the earpiece.
 * - Live Broadcast: Speakerphone.
 * - Gaming Voice: Speakerphone.
 *
 * @param defaultToSpeaker A boolean value that sets the default audio route:
 *      - YES: Sets the speakerphone as the default audio route.
 *      - NO: (Default) Sets the earpiece as the default audio route.
 *
 * @return
 * - `0`: Indicates the method call was successful and the default audio route has been set as specified.
 * - A negative value: Indicates a failure to set the default audio route, with specific error codes providing further details.
 */

// Note: Properly configure the default audio route according to the user's needs and the application's audio requirements before joining a channel.
- (int)setDefaultAudioRouteToSpeakerphone:(BOOL)defaultToSpeaker;

/**
 * Enables or disables the routing of audio to the speakerphone. (iOS only)
 *
 * This method determines if the audio should be directed to the speakerphone.
 * After invoking this method, the SDK will trigger the `didAudioRouteChanged` callback to indicate that a change in the audio route has occurred.
 *
 * **Note:**
 * - Make sure that the `joinChannelByToken` method has been successfully called before using this method.
 * - The SDK configures the audio session category with options to manage headset/speakerphone routing, making this method's effect applicable to all system audio playback.
 *
 * @param enableSpeaker A boolean value that specifies the audio routing:
 *      - YES: Directs the audio to the speakerphone.
 *      - NO: Directs the audio to the earpiece. If a headset is connected, the audio is routed to the headset instead.
 *
 * @return
 * - `0`: Indicates the method call was successful and the audio routing has been set as specified.
 * - A negative value: Indicates a failure to set the audio routing, with specific error codes providing further details.
 */

// Note: Use this method to control the audio output device according to the user's preferences and the context of the application.
- (int)setEnableSpeakerphone:(BOOL)enableSpeaker;

/** Checks whether the speakerphone is enabled. (iOS only.)

 @return * YES: The speakerphone is enabled, and the audio plays from the speakerphone.
 * NO: The speakerphone is not enabled, and the audio plays from devices other than the speakerphone. For example, the headset or earpiece.
 */
- (BOOL)isSpeakerphoneEnabled;
#endif


#pragma mark In Ear Monitor

/**-----------------------------------------------------------------------------
 * @name In-ear Monitor
 * -----------------------------------------------------------------------------
 */

#if TARGET_OS_IPHONE

/**
 * Enables or disables in-ear monitoring. (iOS only)
 *
 * This method allows you to activate or deactivate the in-ear monitoring feature, which is useful for live broadcasting and recording scenarios.
 *
 * @param enabled A boolean value that specifies whether in-ear monitoring is enabled:
 *      - YES: In-ear monitoring is enabled.
 *      - NO: In-ear monitoring is disabled by default.
 *
 * @return
 * - `0`: Indicates the method call was successful and in-ear monitoring has been enabled or disabled as specified.
 * - A negative value: Indicates a failure to set in-ear monitoring, with specific error codes providing further details.
 */

// Note: In-ear monitoring is typically used by broadcasters and hosts to monitor their audio in real-time. Ensure this feature is used according to the user's needs and the application's audio requirements.
- (int)enableInEarMonitoring:(BOOL)enabled;

/** Sets the volume of the in-ear monitor. (iOS only.)

 @param volume Sets the volume of the in-ear monitor. The value ranges between 0 and 100 (default).

 @return * 0: Success.
* < 0: Failure.
 */
- (int)setInEarMonitoringVolume:(NSInteger)volume;
#endif


#pragma mark Audio Sound Effect

/**-----------------------------------------------------------------------------
 * @name Audio Sound Effect
 * -----------------------------------------------------------------------------
 */

/**
 * Adjusts the voice pitch of the local speaker.
 *
 * This method allows you to modify the pitch of the voice for the local user. It can be used for various effects or to adapt the voice to different scenarios.
 *
 * @param pitch A floating-point value that sets the voice pitch. The range is between 0.5 (lower pitch) and 2.0 (higher pitch). A value of 1.0 indicates no change to the pitch, which is the default.
 *
 * @return
 * - `0`: Indicates the method call was successful and the voice pitch has been adjusted as specified.
 * - `-1`: Indicates a failure to adjust the voice pitch, with specific error codes providing further details if applicable.
 */

// Note: Use this method to alter the pitch of the local audio for creative or practical purposes, such as voice modification during a live performance or audio recording.
- (int)setLocalVoicePitch:(double)pitch;

/** Sets the local voice equalization effect.

 @param bandFrequency Sets the band frequency. The value ranges between 0 and 9, representing the respective 10-band center frequencies of the voice effects, including 31, 62, 125, 500, 1k, 2k, 4k, 8k, and 16k Hz. See BBRtcAudioEqualizationbandFrequency.
 @param gain          Sets the gain of each band (dB). The value ranges between -15 and 15. The default value is 0.

 @return * 0: Success.
* -1: Failure.
*/
- (int)setLocalVoiceEqualizationOfbandFrequency:(BBRtcAudioEqualizationbandFrequency)bandFrequency withGain:(NSInteger)gain;

/**
 * Sets the local voice reverberation effect.
 *
 * This method enables you to apply a reverberation effect to your local voice, offering various presets that can enhance the audio quality for different scenarios, such as singing or gaming.
 * You can choose from a range of reverberation types, including but not limited to Popular, R&B, Rock, Hip-hop, and others, to achieve the desired audio atmosphere.
 *
 * @param reverbType The type of reverberation effect to apply. For details on the available reverberation types, refer to the BBRtcAudioReverbType enumeration.
 * @param value      The intensity or parameter value for the specified reverberation effect. The specific value range and impact on the reverberation effect depend on the reverbType selected. For the value range, refer to the BBRtcAudioReverbType documentation.
 *
 * @return
 * - `0`: Indicates the method call was successful and the local voice reverberation has been set as specified.
 * - `-1`: Indicates a failure to set the local voice reverberation, with specific error codes providing further details if applicable.
 */

// Note: For a more streamlined approach to applying common reverberation effects, consider using the `setLocalVoiceReverbPreset` method, which provides preset options for quick configuration.
- (int)setLocalVoiceReverbOfType:(BBRtcAudioReverbType)reverbType withValue:(NSInteger)value;

/**
 * Sets the local voice reverberation effect.
 *
 * This method allows you to apply a reverberation effect to the local voice, enhancing the audio experience for scenarios such as singing or live broadcasting.
 * You can select from various preset reverberation effects, including Popular, R&B, Rock, Hip-hop, and others.
 *
 * @param reverbType The type of reverberation effect to apply. For a list of available reverberation types, refer to BBRtcAudioReverbType.
 * @param value      The intensity or setting value for the specified reverberation type. The value range and specific effects depend on the reverbType chosen. For details, refer to BBRtcAudioReverbType.
 *
 * @return
 * - `0`: Indicates the method call was successful and the local voice reverberation has been set as specified.
 * - `-1`: Indicates a failure to set the local voice reverberation, with specific error codes providing further details if applicable.
 */

// Note: Use the `setLocalVoiceReverbPreset` method for a more user-friendly approach to setting common reverberation effects. This method provides a direct way to apply complex reverberation settings with ease.
- (int) setLocalVoiceChanger:(BBRtcAudioVoiceChanger)voiceChanger;

/**
 * Sets the preset local voice reverberation effect.
 *
 * **Note:**
 * - This method should not be used in conjunction with `setLocalVoiceReverbOfType:withValue:`.
 * - It should not be used together with `setLocalVoiceChanger:`. If both methods are called, the one called earlier will not produce the expected effect.
 *
 * @param reverbPreset The preset option for the local voice reverberation effect. For available preset options, refer to BBRtcAudioReverbPreset.
 *
 * @return
 * - `0`: Indicates the method call was successful and the preset reverberation effect has been applied.
 * - `-1`: Indicates a failure to set the preset reverberation effect, with specific error codes providing further details if applicable.
 */

// Note: Choose the appropriate preset based on the desired audio effect for your application, keeping in mind the compatibility with other voice processing methods.
- (int) setLocalVoiceReverbPreset:(BBRtcAudioReverbPreset)reverbPreset;


#pragma mark Music File Playback and Mixing

/**-----------------------------------------------------------------------------
 * @name Music File Playback and Mixing
 * -----------------------------------------------------------------------------
 */

/**
 * Starts audio mixing by combining a specified local or online audio file with the microphone audio stream or replacing it.
 *
 * This method enables audio mixing, allowing you to:
 * - Mix the specified local audio file with the audio stream from the microphone.
 * - Replace the microphone's audio stream entirely with the specified local audio file.
 * You can also decide if others in the call should hear the local audio playback and set the number of times the audio file should loop during playback. Online music playback is supported.
 *
 * A successful call to `startAudioMixing` triggers the `localAudioMixingStateDidChanged` callback with `BBRtcAudioMixingStatePlaying` on the local client.
 *
 * When the audio mixing file playback is finished, the `localAudioMixingStateDidChanged` callback with `BBRtcAudioMixingStateStopped` is triggered on the local client.
 *
 * **Note:**
 * - Ensure the iOS device is running version 8.0 or later to use this method.
 * - This method should be called while inside a channel.
 * - When playing an online music file, ensure a delay of over 100 ms between the music playback and calling this method to avoid the `AudioFileOpenTooFrequent(702)` warning.
 * - If the local audio mixing file is missing, the file format is not supported, or the music file URL cannot be accessed, the SDK will return `BBRtcWarningCodeAudioMixingOpenError(701)`.
 *
 * @param filePath The absolute path of the local or online audio file to be used for mixing. Supported formats include mp3, aac, m4a, 3gp, and wav.
 * @param loopback A boolean value that determines which user can hear the audio mixing:
 *      - YES: Only the local user can hear the audio mixing.
 *      - NO: Both the local user and others in the call can hear the audio mixing.
 * @param replace A boolean value that sets the content of the audio mixing:
 *      - YES: Only the specified audio file is published; the microphone's audio stream is not.
 *      - NO: The local audio file is mixed with the microphone's audio stream.
 * @param cycle An integer that sets the number of playback loops for the audio file:
 *      - A positive integer indicates the exact number of loops.
 *      - -1 indicates an infinite number of playback loops.
 *
 * @return
 * - `0`: Indicates the method call was successful and audio mixing has started as configured.
 * - A negative value: Indicates a failure to start audio mixing, with specific error codes providing further details.
 */

// Note: Use this method to enhance the audio experience during calls by incorporating local or online audio files, with options for privacy or shared listening and loop settings for continuous playback.
- (int)startAudioMixing:(NSString *  _Nonnull)filePath
               loopback:(BOOL)loopback
                replace:(BOOL)replace
                  cycle:(NSInteger)cycle;

- (int)startAudioMixing:(NSString *  _Nonnull)filePath
               loopback:(BOOL)loopback
                replace:(BOOL)replace
                  cycle:(NSInteger)cycle
                  startPos:(NSInteger)startPos;


/**
 * Stops audio mixing.
 *
 * Use this method to cease the audio mixing process while you are in a channel.
 *
 * @return
 * - `0`: Indicates the method call was successful and audio mixing has been stopped.
 * - A negative value: Indicates a failure to stop audio mixing, with specific error codes providing further details.
 */

// Note: Call this method when you wish to end the audio mixing session during a call to ensure proper termination of the audio playback.
- (int)stopAudioMixing;

/**
 * Pauses audio mixing.
 *
 * This method is used to temporarily suspend the audio mixing process while you are in a channel.
 * It can be useful for scenarios where you need to interrupt the audio playback without stopping it completely.
 *
 * @return
 * - `0`: Indicates the method call was successful and audio mixing has been paused.
 * - A negative value: Indicates a failure to pause audio mixing, with specific error codes providing further details.
 */

// Note: Utilize this method to manage audio mixing during live interactions, allowing for可控 pauses in the audio playback as needed.
- (int)pauseAudioMixing;

/**
 * Resumes audio mixing.
 *
 * Use this method to continue the audio mixing process after it has been paused while you are in a channel.
 * This is useful for resuming audio playback following a可控 pause or interruption.
 *
 * @return
 * - `0`: Indicates the method call was successful and audio mixing has been resumed.
 * - A negative value: Indicates a failure to resume audio mixing, with specific error codes providing further details.
 */

// Note: Employ this method to manage the flow of audio during a session, allowing for dynamic control over the audio playback.
- (int)resumeAudioMixing;

/**
 * Adjusts the volume of audio mixing.
 *
 * This method is used to modify the volume level of the audio mixing while you are in a channel.
 * It allows you to control the loudness of the mixed audio to suit your needs or preferences.
 *
 * **Note:**
 * - This method's effect is independent of the audio effect file playback volume, which is controlled by the `playEffect` method.
 *
 * @param volume The volume level for the audio mixing, with a range from 0 (silent) to 100 (maximum volume). The default value is set to 100.
 *
 * @return
 * - `0`: Indicates the method call was successful and the audio mixing volume has been adjusted as specified.
 * - A negative value: Indicates a failure to adjust the audio mixing volume, with specific error codes providing further details if applicable.
 */

// Note: Use this method to fine-tune the audio mixing volume during a call, ensuring the audio playback is at the desired loudness for the audience.
- (int)adjustAudioMixingVolume:(NSInteger)volume;

/**
 * Adjusts the volume of audio mixing for local playback.
 *
 * Use this method to control the volume level of the audio mixing that you hear locally while you are in a channel.
 * This setting allows you to increase or decrease the volume of the mixed audio for your own listening experience.

 * @param volume The volume level for local playback of the audio mixing, ranging from 0 (silent) to 100 (maximum volume). The default is typically set to 100.
 *
 * @return
 * - `0`: Indicates the method call was successful and the local playback volume has been set as specified.
 * - A negative value: Indicates a failure to set the local playback volume, with specific error codes providing further details if applicable.
 */

// Note: This method is useful for adjusting the volume of the mixed audio stream that you, as the local user, hear. It does not affect the volume heard by other participants in the channel.
- (int)adjustAudioMixingPlayoutVolume:(NSInteger)volume;

/**
 * Adjusts the volume of audio mixing for publishing to other users.
 *
 * Use this method to set the volume level of the audio mixing that will be sent to other users in the channel.
 * This allows you to control how loud the mixed audio is for remote participants during the call.

 * @param volume The volume level for the audio mixing when published to other users, with a range from 0 (silent) to 100 (maximum volume). The default is typically set to 100.
 *
 * @return
 * - `0`: Indicates the method call was successful and the publish volume has been adjusted as specified.
 * - A negative value: Indicates a failure to adjust the publish volume, with specific error codes providing further details if applicable.
 */

// Note: Adjust this setting to ensure that the audio mixing is transmitted at the desired volume level to other users in the channel. This does not affect your local playback volume.
- (int)adjustAudioMixingPublishVolume:(NSInteger)volume;

/** Gets the audio mixing volume for publishing.

This method helps troubleshoot audio volume related issues.
*/
- (int)getAudioMixingPublishVolume;

/** Gets the audio mixing volume for local playback.

This method helps troubleshoot audio volume related issues.
*/
- (int)getAudioMixingPlayoutVolume;

/**
 * Retrieves the duration of audio mixing in milliseconds.
 *
 * Use this method to get the total playback duration of the audio mixing while you are in a channel.
 * This can be useful for monitoring the length of the audio that has been mixed and played.

 * @return
 * - A value greater than or equal to 0: Indicates the method call was successful and represents the audio mixing duration in milliseconds.
 * - A negative value: Indicates a failure to retrieve the audio mixing duration, with specific error codes providing further details if applicable.
 */

// Note: This method provides the duration of the audio that has been mixed, which can be helpful for tracking playback lengths during a session.
- (int)getAudioMixingDuration;

/**
 * Retrieves the current playback position of the audio mixing file in milliseconds.
 *
 * Use this method to find out the exact position in the audio mixing file that is currently being played while you are in a channel.
 * This feature is helpful for implementing features such as progress tracking or seeking within the audio file.

 * @return
 * - A value greater than or equal to 0: Indicates the method call was successful and represents the current playback position of the audio mixing file in milliseconds.
 * - A negative value: Indicates a failure to retrieve the playback position, with specific error codes providing further details if applicable.
 */

// Note: This method is useful for audio applications that require precise control over and insight into the playback of audio mixing files during a session.
- (int)getAudioMixingCurrentPosition;

/**
 * Sets a custom playback starting position for the audio mixing file.
 *
 * Use this method to specify a starting position other than the beginning of the audio mixing file. This allows for more flexible audio playback scenarios, such as replaying a specific segment of the audio.
 *
 * @param pos The new playback starting position in milliseconds within the audio mixing file.
 *
 * @return
 * - `0`: Indicates the method call was successful and the playback position has been set as specified.
 * - A negative value: Indicates a failure to set the playback position, with specific error codes providing further details if applicable.
 */

// Note: This method provides the capability to jump to a specific time point within the audio mixing file, enabling features like audio segmentation or precise control over playback start times.
- (int)setAudioMixingPosition:(NSInteger)pos;

- (int)setAudioMixingPitch:(NSInteger)pitch;
#pragma mark Audio Effect File Playback

/**-----------------------------------------------------------------------------
 * @name Audio Effect File Playback
 * -----------------------------------------------------------------------------
 */

/**
 * Retrieves the current volume setting for audio effects.
 *
 * This method is used to get the volume level at which the audio effects are being played.
 * The volume value is expressed as a float, ranging from 0.0 (silent) to 100.0 (maximum volume).

 * @return
 * - A value greater than or equal to 0: Represents the volume of the audio effects if the method call is successful.
 * - A negative value: Indicates a failure to retrieve the volume of the audio effects, with specific error codes providing further details if applicable.
 */

// Note: Use this method to check the volume level of audio effects, which can help in adjusting the balance between effects and other audio elements in the mix.
- (double)getEffectsVolume;

/**
 * Sets the volume for audio effects.
 *
 * This method allows you to adjust the volume level of the audio effects within the application.
 * The volume can be set to a value between 0.0 (silent) and 100.0 (maximum volume), with 100.0 being the default.

 * @param volume The volume level for the audio effects, where the value ranges from 0.0 to 100.0.
 *
 * @return
 * - `0`: Indicates the method call was successful and the audio effects volume has been set as specified.
 * - A negative value: Indicates a failure to set the audio effects volume, with specific error codes providing further details if applicable.
 */

// Note: Use this method to control the loudness of audio effects, ensuring they are neither too quiet nor overpowering in the context of your audio mix.
- (int)setEffectsVolume:(double)volume;

/**
 * Sets the volume for a specified audio effect.
 *
 * Use this method to adjust the volume level of an individual audio effect identified by its unique `soundId`.
 * You can set the volume to any value between 0.0 (silent) and 100.0 (maximum volume), with 100.0 being the default level.

 * @param soundId The unique identifier for the audio effect whose volume is to be set.
 * @param volume The desired volume level for the specified audio effect, ranging from 0.0 to 100.0.
 *
 * @return
 * - `0`: Indicates the method call was successful and the volume for the specified audio effect has been set as requested.
 * - A negative value: Indicates a failure to set the volume for the specified audio effect, with specific error codes providing further details if applicable.
 */

// Note: This method enables individual control over the volume of different audio effects, allowing for precise audio mixing and user experience customization.
- (int)setVolumeOfEffect:(int)soundId
              withVolume:(double)volume;

/**
 * Plays a specified audio effect, allowing customization for various scenarios such as gaming.
 *
 * This method enables the addition of specific audio effects and provides control over the loop count, pitch, pan, and gain of the audio file.
 * You can also determine whether the remote user can hear the audio effect.
 *
 * To play multiple audio effect files at the same time, call this method multiple times with different `soundId` and `filePath` parameters.
 * It is recommended to limit the simultaneous playback to no more than three audio effect files.
 *
 * Upon completion of the audio effect file playback, the SDK triggers the `rtcEngineDidAudioEffectFinish` callback.
 *
 * **Note:**
 * - Playing multiple online audio effect files simultaneously is not supported on macOS.
 * - If the audio effect is preloaded into memory using the `preloadEffect` method, ensure the `soundId` matches the one set in the `preloadEffect` method.
 *
 * @param soundId The unique identifier for the audio effect. This ID is necessary if the audio effect is preloaded and must be consistent.
 * @param filePath The absolute path to the local audio effect file or the URL for the online audio effect file.
 * @param loopCount The number of times the audio effect should loop:
 *      - 0: The audio effect plays once.
 *      - 1: The audio effect plays twice.
 *      - -1: The audio effect loops indefinitely until the `stopEffect` or `stopAllEffects` method is called.
 * @param pitch The pitch of the audio effect, with a range from 0.5 to 2. The default is 1 (no pitch change). Lower values result in a lower pitch.
 * @param pan The spatial position of the audio effect, ranging from -1.0 to 1.0:
 *      - 0.0: The audio effect is centered.
 *      - 1.0: The audio effect is positioned to the right.
 *      - -1.0: The audio effect is positioned to the left.
 * @param gain The volume of the audio effect, with a range from 0.0 to 100.0. The default is 100.0. Lower values decrease the volume.
 * @param publish A boolean value that determines if the audio effect is published to the remote stream:
 *      - YES: The audio effect is published to the BBRtc Cloud, allowing remote users to hear it.
 *      - NO: The audio effect is not published, and remote users cannot hear it.
 *
 * @return
 * - `0`: Indicates the method call was successful and the audio effect will play as configured.
 * - A negative value: Indicates a failure to play the audio effect, with specific error codes providing further details if applicable.
 */

// Note: Use this method to enhance user experiences by adding customized audio effects that can be heard by either the local user, remote users, or both, based on the `publish` parameter.
- (int)playEffect:(int)soundId
         filePath:(NSString * _Nullable)filePath
        loopCount:(int)loopCount
            pitch:(double)pitch
              pan:(double)pan
             gain:(double)gain
          publish:(BOOL)publish;

- (int)playEffect:(int)soundId
         filePath:(NSString * _Nullable)filePath
        loopCount:(int)loopCount
            pitch:(double)pitch
              pan:(double)pan
             gain:(double)gain
          publish:(BOOL)publish
          startPos:(int)startPos;

/** Stops playing a specified audio effect.

 @param soundId ID of the audio effect. Each audio effect has a unique ID.

 @return * 0: Success.
* < 0: Failure.
 */
- (int)stopEffect:(int)soundId;

/** Stops playing all audio effects state.
 */
- (int)stopAllEffects;

/**
 * Preloads a specified audio effect file into memory.
 *
 * To ensure smooth audio playback during communication, it is recommended to preload the audio effect file using this method before joining a channel with `joinChannelByToken`.
 * This preloading process helps in reducing latency and provides a better user experience by preparing the audio file for immediate use.
 *
 * Supported audio formats for preloading include mp3, aac, m4a, 3gp, and wav.
 *
 * **Note:**
 * - This method is not designed to handle online audio effect files and only works with locally stored files.
 *
 * @param soundId  The unique identifier for the audio effect being preloaded. Each audio effect must have a unique ID for proper reference.
 * @param filePath The absolute file path of the audio effect file that will be loaded into memory.
 *
 * @return
 * - `0`: Indicates the method call was successful and the audio effect file has been preloaded into memory.
 * - A negative value: Indicates a failure to preload the audio effect file, with specific error codes providing further details if applicable.
 */

// Note: Preloading audio effects is a best practice to prepare for seamless audio playback in real-time communication scenarios, reducing the impact of streaming delays.
- (int)preloadEffect:(int)soundId
            filePath:(NSString * _Nullable)filePath;

/**
 * Stops playing a specified audio effect.
 *
 * Use this method to cease the playback of an individual audio effect identified by its unique `soundId`.
 * This is useful for scenarios where you need to stop an audio effect before it has finished playing or looped.

 * @param soundId The unique identifier for the audio effect that should stop playing.
 *
 * @return
 * - `0`: Indicates the method call was successful and the specified audio effect has been stopped.
 * - A negative value: Indicates a failure to stop the specified audio effect, with specific error codes providing further details if applicable.
 */

// Note: This method provides control over the termination of audio effects, allowing for dynamic audio management during various application scenarios.
- (int)unloadEffect:(int)soundId;

/** Pauses a specified audio effect.

 @param soundId ID of the audio effect. Each audio effect has a unique ID.

 @return * 0: Success.
* < 0: Failure.
 */
- (int)pauseEffect:(int)soundId;

/**control  Pauses all audio effects.

 @return * 0: Success.
* < 0: Failure.
 */
- (int)pauseAllEffects;

/** control Resumes playing a specified audio effect.

 @param soundId ID of the audio effect. Each audio effect has a unique ID.

 @return * 0: Success.
* < 0: Failure.
 */
- (int)resumeEffect:(int)soundId;

/** control  Resumes playing all audio effects.

 @return * 0: Success.
* < 0: Failure.
 */
- (int)resumeAllEffects;

- (int)getEffectCurrentPosition:(int)soundId;

- (int)setEffectPosition:(int)soundId pos:(NSInteger)pos;

- (int)getEffectDuration:(NSString* _Nonnull)filePath;
#pragma mark Audio Recorder

/**-----------------------------------------------------------------------------
 * @name Audio Recorder
 * -----------------------------------------------------------------------------
 */

/**
 * Starts an audio recording on the client.
 *
 * The SDK facilitates audio recording during a call. By successfully invoking this method, you can capture the audio of all users in the channel and obtain an audio recording file. The supported formats for the recording file include:
 * - .wav: Offers large file size with high fidelity, suitable for high-quality requirements.
 * - .aac: Results in a smaller file size with lower fidelity, suitable for bandwidth efficiency.
 *
 * **Note:**
 * - Make sure that the directory for saving the recording file is accessible and has write permissions.
 * - This method is typically called after joining the channel with `joinChannelByToken`. The recording will automatically cease when `leaveChannel` is invoked.
 * - For optimal recording quality, set the `quality` to `BBRtcAudioRecordingQualityMedium` or `BBRtcAudioRecordingQualityHigh` when the `sampleRate` is set to 44100 Hz or 48000 Hz.
 *
 * @param filePath The absolute file path for the recording file, with the filename encoded in UTF-8.
 * @param sampleRate The sample rate in Hz for the recording file, with supported values including:
 *     - 16000
 *     - (Default) 32000
 *     - 44100
 *     - 48000
 * @param quality The desired audio recording quality, detailed in the BBRtcAudioRecordingQuality enumeration.
 *
 * @return
 * - `0`: Indicates the method call was successful and the audio recording has started.
 * - A negative value: Indicates a failure to start the audio recording, with specific error codes providing further details if applicable.
 */

// Note: Properly configure the recording parameters to balance file size and audio quality according to the application's needs and the available storage space.
- (int)startAudioRecording:(NSString * _Nonnull)filePath
                   sampleRate:(NSInteger)sampleRate
                   quality:(BBRtcAudioRecordingQuality)quality;

/** control Stops an audio recording on the client.
 @return * 0: Success.
* < 0: Failure.
 */
- (int)stopAudioRecording;

#pragma mark Loopback Recording

/**-----------------------------------------------------------------------------
 * @name Loopback Recording
 * -----------------------------------------------------------------------------
 */

#if (!(TARGET_OS_IPHONE) && (TARGET_OS_MAC))
/**
 * Enables or disables loopback recording. (macOS only)
 *
 * Enabling loopback recording allows the output from the sound card to be mixed into the audio stream sent to the remote party.
 *
 * **Note:**
 * macOS does not support loopback recording for the default sound card. To utilize loopback recording, a virtual sound card is required. When using a virtual sound card, such as "Soundflower," pass its name as a parameter. BBRtc has tested and recommends using "Soundflower" for this purpose.
 *
 * @param enabled A boolean value that sets whether loopback recording is enabled or disabled:
 *      - YES: Enables loopback recording.
 *      - NO: Disables loopback recording (default).
 * @param deviceName A pointer to the device name of the sound card. Set to nil (default) to use the default sound card. If using a virtual sound card like "Soundflower," specify its name to direct the SDK to find and use the corresponding sound card for capturing audio.
 *
 * @return
 * - `0`: Indicates the method call was successful and loopback recording has been enabled or disabled as specified.
 * - A negative value: Indicates a failure to set loopback recording, with specific error codes providing further details if applicable.
 */

// Note: Loopback recording is a macOS-specific feature that requires the use of a virtual sound card for capturing system audio output. Ensure the correct configuration for your application's needs.
-(int)enableLoopbackRecording:(BOOL)enabled
                   deviceName:(NSString * _Nullable)deviceName;
#endif


#pragma mark Miscellaneous Audio Control
#pragma mark Network-related Test

#pragma mark Custom Video Module

/**-----------------------------------------------------------------------------
 * @name Custom Video Module
 * -----------------------------------------------------------------------------
 */

/** control Sets the video source.

In real-time communications, the SDK uses the default video input source (the built-in camera) to publish streams. To use an external video source, call BBRtcVideoSourceProtocol to set the custom video source and then use this method to add the external video source into the SDK.

 @param videoSource BBRtcVideoSourceProtocol
 */
- (void)setVideoSource:(id<BBRtcVideoSourceProtocol> _Nullable)videoSource;

/** control Sets the local video renderer.

In real-time communications, the SDK uses the default video renderer to render the video. To use an external video renderer, call BBRtcVideoSinkProtocol to set the custom local video renderer and then use this method to add the external renderer into the SDK.

 @param videoRenderer Sets the local video renderer. See BBRtcVideoSinkProtocol.
 */
- (void)setLocalVideoRenderer:(id<BBRtcVideoSinkProtocol> _Nullable)videoRenderer;

/** control  Sets the remote video renderer.

 This method sets the remote renderer. In real-time communications, the SDK uses the default video renderer to render the video. To use an external video renderer, call BBRtcVideoSinkProtocol to set the custom remote video renderer and then use this method to add the external renderer into the SDK.

 @param videoRenderer Sets the video renderer of the remote user. See BBRtcVideoSinkProtocol.
 @param userId ID of the remote user.
 */
- (void)setRemoteVideoRenderer:(id<BBRtcVideoSinkProtocol> _Nullable)videoRenderer forUserId:(NSUInteger)userId;

/**control Retrieves the video source.

  @return Video source. See BBRtcVideoSourceProtocol.
 */
- (id<BBRtcVideoSourceProtocol> _Nullable)videoSource;

/** control Retrieves the local video renderer.

 @return Local video renderer. See BBRtcVideoSinkProtocol.
 */
- (id<BBRtcVideoSinkProtocol> _Nullable)localVideoRenderer;

/** control Retrieves the video renderer of a specified remote user.

 @param userId ID of the remote user.
 @return Video renderer of the remote user. See BBRtcVideoSinkProtocol.
 */
- (id<BBRtcVideoSinkProtocol> _Nullable)remoteVideoRendererOfUserId:(NSUInteger)userId;

/**
 * Registers a protocol for handling raw video frames.
 *
 * Once the raw video frame protocol is successfully registered, the SDK will invoke the callbacks you have implemented in the BBRtcVideoDataFrameProtocol each time a video frame is received. This allows for custom processing of video data as needed.
 *
 * **Note:**
 * - This method is only applicable to iOS.
 * - Make sure to call this method before joining a channel.
 * - Be aware that the dimensions of the video obtained through the protocol may vary due to factors such as poor network conditions or changes in user-adjusted resolution.
 *
 * @param videoData An object conforming to the BBRtcVideoDataFrameProtocol for receiving and handling raw video frames. If `nil` is provided, the registration of the protocol is canceled.
 *
 * @returns
 * - `0`: Indicates the method call was successful and the protocol has been registered or deregistered.
 * - A negative value: Indicates a failure to register the protocol, with specific error codes providing further details if applicable.
 */

// Note: Utilize this feature to implement custom video processing or analysis within your application, taking advantage of direct access to raw video frame data.
- (void)setVideoDataFrame:(id<BBRtcVideoDataFrameProtocol> _Nullable)videoData;

#pragma mark External Audio Data
/**
 * Enables the external audio sink for custom audio playback scenarios.
 *
 * This method is used when you intend to utilize external audio data for playback. By enabling the external audio sink, you can extract remote audio data through the `pullPlaybackAudioFrameRawData` or `pullPlaybackAudioFrameSampleBufferByLengthInByte` methods, process it as needed, and then play it back with desired audio effects.
 *
 * @param sampleRate Sets the sample rate in Hertz for the external audio sink. Choose from 16000, 32000, 44100, or 48000 to match your audio requirements.
 * @param channels Sets the number of audio channels for the external audio sink:
 *     - 1: Mono channel for a single audio channel output.
 *     - 2: Stereo channel for dual audio channel output.
 *
 * **Note:**
 * Once the external audio sink is enabled, the app will no longer receive audio data through the `onPlaybackAudioFrame` callback. This indicates that the internal audio processing is bypassed in favor of the external audio sink.
 */

// Note: Use this method to integrate custom audio processing and playback solutions, allowing for advanced audio manipulation and effects when handling remote audio streams.
- (void)enableExternalAudioSink:(NSUInteger)sampleRate
                               channels:(NSUInteger)channels;

/** control Disables the external audio sink.
 */
- (void)disableExternalAudioSink;

/**
 * Pulls the remote audio data in the RawData format for external processing and playback.
 *
 * Before using this method, ensure that you have enabled and configured the external audio sink using the `enableExternalAudioSink` method.
 * Once this method is successfully called, the app can retrieve the decoded and mixed audio data intended for playback.
 *
 * **Note:**
 * - After a successful call to `pullPlaybackAudioFrameRawData`, the app will no longer receive audio data through the `onPlaybackAudioFrame` callback.
 * - The distinction between the `onPlaybackAudioFrame` callback and the `pullPlaybackAudioFrameRawData` method is as follows:
 *     - `onPlaybackAudioFrame`: The SDK delivers audio data to the app every 10 ms, and processing delays may lead to audio jitter.
 *     - `pullPlaybackAudioFrameRawData`: The app autonomously pulls the remote audio data. After audio data parameters are set, the SDK adjusts the frame buffer to prevent jitter issues in external audio playback.
 *
 * @param data The buffer in which the audio data will be stored. The data format is a byte array.
 * @param lengthInByte The length of the data in bytes to pull from the external audio source.
 *
 * The value of `lengthInByte` should be calculated based on the `sampleRate` set in the `enableExternalAudioSink` method as follows: 
 * lengthInByte = (sampleRate / 100) * 2 * number of channels * time (ms).
 *
 * @return
 * - YES: Indicates the method call was successful and the audio data has been pulled.
 * - NO: Indicates a failure to pull the audio data.
 */

// Note: Use this method to manage the retrieval of remote audio data for scenarios requiring custom audio playback or processing, providing more control over the audio stream handling.
- (BOOL)pullPlaybackAudioFrameRawData:(void * _Nonnull)data
                              lengthInByte:(NSUInteger)lengthInByte;

/**
 * Pulls the remote audio data in the SampleBuffer format for external processing and playback.
 *
 * Before utilizing this method, ensure that you have enabled and configured the external audio sink using the `enableExternalAudioSink` method.
 * Upon a successful invocation of this method, the app can retrieve the decoded and mixed audio data ready for playback.
 *
 * **Note:**
 * - After a successful call to `pullPlaybackAudioFrameSampleBufferByLengthInByte`, the app will no longer receive audio data through the `onPlaybackAudioFrame` callback.
 * - The distinction between the `onPlaybackAudioFrame` callback and the `pullPlaybackAudioFrameSampleBufferByLengthInByte` method is outlined as follows:
 *     - `onPlaybackAudioFrame`: The SDK delivers audio data to the app every 10 ms, and processing delays may lead to audio jitter.
 *     - `pullPlaybackAudioFrameSampleBufferByLengthInByte`: The app autonomously pulls the remote audio data. Post-configuration of the audio data parameters, the SDK adjusts the frame buffer, mitigating jitter-related issues in external audio playback.
 *
 * @param lengthInByte The length of the external audio data in bytes to be pulled.
 *
 * The value of `lengthInByte` should be calculated in relation to the sample rate set in the `enableExternalAudioSink` method as follows:
 *   - `lengthInByte` = (`sampleRate` / 100) * 2 * number of channels * time (ms).
 * Ensure that this parameter is divisible by the sample rate for proper audio data processing.
 *
 * @return
 * - YES: Indicates the method call was successful, and the audio data has been pulled.
 * - NO: Indicates a failure to pull the audio data.
 */

// Note: Employ this method for scenarios that require custom handling of remote audio streams, offering greater control over audio playback and processing compared to the standard callback approach.
- (CMSampleBufferRef _Nullable)pullPlaybackAudioFrameSampleBufferByLengthInByte:(NSUInteger)lengthInByte;

/**
 * -----------------------------------------------------------------------------
 * @name External Audio Data (push-mode only)
 * -----------------------------------------------------------------------------
 */

/**
 * Enables the external audio source for push-mode operations.
 *
 * This method should be called before joining the channel to configure the external audio source settings.
 * It allows the use of an external audio source instead of the default built-in microphone for capturing audio.
 *
 * @param sampleRate       The sample rate in Hertz for the external audio source. Choose from 8000, 16000, 44100, or 48000 Hz to match the desired audio quality and application requirements.
 * @param channelsPerFrame The number of channels for the external audio source:
 *     - 1: Mono, indicating a single audio channel.
 *     - 2: Stereo, indicating two audio channels.
 *
 * Enabling the external audio source allows for advanced audio capture scenarios, such as using professional audio equipment for higher quality audio input.
 */

// Note: Properly configure the external audio source parameters before joining the channel to ensure seamless integration with the audio processing pipeline in push-mode scenarios.
- (void)enableExternalAudioSourceWithSampleRate:(NSUInteger)sampleRate
                               channelsPerFrame:(NSUInteger)channelsPerFrame;

/** control Disables the external audio source.
 */
- (void)disableExternalAudioSource;

/**
 * Pushes external raw audio frame data to the SDK for encoding.
 *
 * This method is used to send audio data from an external source to the SDK for further processing and encoding.
 * It is particularly useful for scenarios where custom audio processing is required before the audio is sent through the channel.
 *
 * @param data      The buffer containing the external audio data to be pushed for encoding.
 * @param samples   The number of samples in the audio data buffer being pushed.
 * @param timestamp The timestamp associated with the external audio frame. This parameter is mandatory and serves multiple purposes:
 *     - It helps restore the order of the captured audio frames, ensuring proper sequencing.
 *     - It can synchronize audio and video frames, especially in video-related scenarios, including those where external video sources are integrated.
 *
 * @return
 * - `0`: Indicates the method call was successful and the audio data has been pushed for encoding.
 * - A negative value: Indicates a failure to push the audio data, with specific error codes providing further details if applicable.
 */

// Note: Accurate timestamping is crucial for maintaining audio integrity and synchronizing multimedia content. Ensure the external audio data is properly timestamped before pushing it to the SDK.
- (BOOL)pushExternalAudioFrameRawData:(void * _Nonnull)data
                              samples:(NSUInteger)samples
                            timestamp:(NSTimeInterval)timestamp;

/**
 * Pushes the external CMSampleBuffer audio frame to the SDK for encoding.
 *
 * Use this method to submit an external CMSampleBuffer containing audio data to the SDK, which will then encode it for transmission.
 * This is particularly useful for integrating with other audio processing systems or frameworks that provide audio data in CMSampleBuffer format.

 * @param sampleBuffer The CMSampleBuffer object containing the audio frame to be encoded and pushed to the channel.
 *
 * @return
 * - YES: Indicates the method call was successful and the audio frame has been pushed for encoding.
 * - NO: Indicates a failure to push the audio frame, with specific error codes providing further details if applicable.
 */

// Note: When working with CMSampleBuffer, ensure that the buffer is properly configured and contains valid audio data before pushing it to the SDK for encoding.
- (BOOL)pushExternalAudioFrameSampleBuffer:(CMSampleBufferRef _Nonnull)sampleBuffer;


#pragma mark External Video Data
#pragma mark Raw Audio Data

/**-----------------------------------------------------------------------------
 * @name Raw Audio Data
 * -----------------------------------------------------------------------------
 */

/**
 * Sets the audio recording format for the `onRecordAudioFrame` callback.
 *
 * For more information on handling raw audio data, see the [Raw Audio Data documentation](https://docs.BBRtc.io/en/Interactive%20Broadcast/raw_data_audio_apple?platform=iOS).
 *
 * **Note:**
 * The SDK calculates the sample interval based on the `sampleRate`, `channel`, and `samplesPerCall` parameters you set in this method.
 * The formula to calculate the sample interval is: Sample interval (sec) = `samplesPerCall` / (`sampleRate` * `channel`).
 * Ensure that the sample interval value is no less than 0.01 seconds. The SDK triggers the `onRecordAudioFrame` callback based on this calculated sample interval.
 *
 * @param sampleRate     The audio sample rate in Hertz (`samplesPerSec`) for the data returned in the `onRecordAudioFrame` callback.
 *                       It can be set to 8000, 16000, 32000, 44100, or 48000 Hz to match the desired audio quality.
 * @param channel        The number of audio channels for the data returned in the `onRecordAudioFrame` callback.
 *                       It can be set to 1 for Mono or 2 for Stereo, affecting the audio data structure.
 * @param mode           The use mode of the `onRecordAudioFrame` callback. For available modes, refer to BBRtcAudioRawFrameOperationMode.
 * @param samplesPerCall The number of samples per callback invocation for the `onRecordAudioFrame`. For RTMP streaming, it is recommended to set this to 1024.
 *
 * @return
 * - `0`: Indicates the method call was successful and the audio recording format has been set.
 * - A negative value: Indicates a failure to set the audio recording format, with specific error codes providing further details if applicable.
 */

// Note: Properly configuring the audio recording format is essential for the correct handling of audio data within your application, especially when processing raw audio frames for callbacks.
- (int)setRecordingAudioFrameParametersWithSampleRate:(NSInteger)sampleRate
                                              channel:(NSInteger)channel
                                                 mode:(BBRtcAudioRawFrameOperationMode)mode
                                       samplesPerCall:(NSInteger)samplesPerCall;
/**
 * Sets the audio playback format for the `onPlaybackAudioFrame` callback.
 *
 * For more information on handling raw audio data, see the [Raw Audio Data documentation](https://docs.BBRtc.io/en/Interactive%20Broadcast/raw_data_audio_apple?platform=iOS).
 *
 * **Note:**
 * The SDK calculates the sample interval based on the `sampleRate`, `channel`, and `samplesPerCall` parameters you set in this method.
 * The formula to calculate the sample interval is: Sample interval (sec) = `samplesPerCall` / (`sampleRate` * `channel`).
 * Ensure that the sample interval value is no less than 0.01 seconds. The SDK triggers the `onPlaybackAudioFrame` callback based on this calculated sample interval.
 *
 * @param sampleRate     The audio sample rate in Hertz (`samplesPerSec`) for the data returned in the `onPlaybackAudioFrame` callback.
 *                       It can be set to 8000, 16000, 32000, 44100, or 48000 Hz to match the desired audio quality.
 * @param channel        The number of audio channels for the data returned in the `onPlaybackAudioFrame` callback.
 *                       It can be set to 1 for Mono or 2 for Stereo, affecting the audio data structure.
 * @param mode           The use mode of the `onPlaybackAudioFrame` callback. For available modes, refer to BBRtcAudioRawFrameOperationMode.
 * @param samplesPerCall The number of samples per callback invocation for the `onPlaybackAudioFrame`. For RTMP streaming, it is recommended to set this to 1024.
 *
 * @return
 * - `0`: Indicates the method call was successful and the audio playback format has been set.
 * - A negative value: Indicates a failure to set the audio playback format, with specific error codes providing further details if applicable.
 */

// Note: Properly configuring the audio playback format is essential for the correct handling of audio data within your application, especially when processing raw audio frames for callbacks.
- (int)setPlaybackAudioFrameParametersWithSampleRate:(NSInteger)sampleRate
                                             channel:(NSInteger)channel
                                                mode:(BBRtcAudioRawFrameOperationMode)mode
                                      samplesPerCall:(NSInteger)samplesPerCall;

/**
 * Sets the mixed audio format for the `onMixedAudioFrame` callback.
 *
 * For more information on handling raw audio data, see the [Raw Audio Data documentation](https://docs.BBRtc.io/en/Interactive%20Broadcast/raw_data_audio_apple?platform=iOS).
 *
 * **Note:**
 * The SDK calculates the sample interval based on the `sampleRate`, `channel`, and `samplesPerCall` parameters you set in this method.
 * The formula to calculate the sample interval is: Sample interval (sec) = `samplesPerCall` / (`sampleRate` * `channel`).
 * Ensure that the sample interval value is no less than 0.01 seconds. The SDK triggers the `onMixedAudioFrame` callback based on this calculated sample interval.
 *
 * @param sampleRate     The audio sample rate in Hertz (`samplesPerSec`) for the data returned in the `onMixedAudioFrame` callback.
 *                       It can be set to 8000, 16000, 32000, 44100, or 48000 Hz to match the desired audio quality.
 * @param samplesPerCall The number of samples per callback invocation for the `onMixedAudioFrame`. For RTMP streaming, it is recommended to set this to 1024.
 *
 * @return
 * - `0`: Indicates the method call was successful and the mixed audio format has been set.
 * - A negative value: Indicates a failure to set the mixed audio format, with specific error codes providing further details if applicable.
 */

// Note: Properly configuring the mixed audio format is essential for the correct handling of mixed audio data within your application, especially when processing raw audio frames for callbacks.
- (int)setMixedAudioFrameParametersWithSampleRate:(NSInteger)sampleRate
                                   samplesPerCall:(NSInteger)samplesPerCall;



/**
 * Registers the raw audio data protocol.
 *
 * @since v3.4.5
 *
 * To enable the SDK to trigger callbacks that provide raw audio data, use this method to register an audio frame delegate.
 * The delegate must conform to the `BBRtcAudioDataFrameProtocol`, which you need to implement.
 *
 * **Note:**
 * - This method is only applicable to iOS.
 * - Make sure to call this method before joining a channel.
 * - To deregister the audio frame delegate, pass `nil` as the `delegate` parameter.
 * BBRtc recommends calling `setAudioDataFrame(nil)` after receiving the `didLeaveChannelWithStats` callback to properly release resources.
 *
 * @param delegate The delegate that will handle the audio frame events. For details on the protocol, refer to BBRtcAudioDataFrameProtocol.
 *
 * @return
 * - YES: Indicates the method call was successful and the delegate has been registered.
 * - NO: Indicates a failure to register the delegate.
 */

// Note: Proper registration and deregistration of the audio frame delegate is crucial for managing raw audio data callbacks effectively and for resource management.
- (BOOL)setAudioDataFrame:(id<BBRtcAudioDataFrameProtocol> _Nullable)delegate;
#pragma mark Watermark

#pragma mark Stream Fallback

/**-----------------------------------------------------------------------------
 * @name Stream Fallback
 * -----------------------------------------------------------------------------
 */

/**
 * Sets the priority of a remote user's stream.
 *
 * This method should be used in conjunction with the `setRemoteSubscribeFallbackOption` method. When the fallback function is enabled for a remote stream, the SDK prioritizes the stream of the user with the highest priority to ensure they receive the best possible stream quality under network constraints.
 *
 * **Note:**
 * The SDK allows setting a high priority (`userPriority`) for only one user at a time. If you set a high priority for a different user, the previously prioritized user will have their priority changed to normal.
 *
 * @param uid The user ID of the remote user whose stream priority you want to set.
 * @param userPriority The priority level for the remote user. For available priority levels, refer to the BBRtcUserPriority enumeration.
 *
 * @return
 * - `0`: Indicates the method call was successful and the user priority has been set.
 * - A negative value: Indicates a failure to set the user priority, with specific error codes providing further details if applicable.
 */

// Note: Use this method to control the quality of service for specific remote users by setting their priority, which is particularly useful in scenarios with limited bandwidth or poor network conditions.
- (int)setRemoteUserPriority:(NSUInteger)uid
                        type:(BBRtcUserPriority)userPriority;

/**
 * Sets the fallback option for the locally published video stream based on network conditions.
 *
 * By default, the `option` is set to `BBRtcStreamFallbackOptionDisabled`, meaning there is no fallback behavior for the locally published video stream when uplink network conditions are poor.
 *
 * If `option` is set to `BBRtcStreamFallbackOptionAudioOnly`, the SDK will:
 * - Disable the upstream video and enable audio only when the network conditions are not sufficient to support both, ensuring continuous communication with minimal quality.
 * - Re-enable the video stream when the network conditions improve to support video transmission again.
 *
 * When the published video stream falls back to audio-only or switches back to video, the SDK triggers the `didLocalPublishFallbackToAudioOnly` callback to notify the application of the change.
 *
 * **Note:**
 * BBRtc does not recommend using this method for CDN live streaming scenarios, as remote CDN live users may experience a noticeable delay when the published video stream falls back to audio-only.
 *
 * @param option The fallback option for the published video stream. The default value is `BBRtcStreamFallbackOptionDisabled`. For available options, refer to the BBRtcStreamFallbackOptions enumeration.
 *
 * @return
 * - `0`: Indicates the method call was successful and the fallback option has been set.
 * - A negative value: Indicates a failure to set the fallback option, with specific error codes providing further details if applicable.
 */

// Note: Choose the appropriate fallback option to ensure the best user experience in varying network conditions, especially when publishing streams that will be consumed in live scenarios.
- (int)setLocalPublishFallbackOption:(BBRtcStreamFallbackOptions)option;

/**
 * Sets the fallback option for remotely subscribed video streams in response to network conditions.
 *
 * By default, the `option` is set to `BBRtcStreamFallbackOptionVideoStreamLow`, which means that under unreliable downlink network conditions, the remotely subscribed video stream will switch to a low-quality stream with reduced resolution and bitrate.
 *
 * If `option` is set to `BBRtcStreamFallbackOptionAudioOnly`, the SDK will automatically transition the video from a high to a low stream, or it will disable the video stream entirely when the downlink network conditions are insufficient to support both audio and video. This ensures that the audio quality is maintained. The SDK continuously monitors the network quality and will re-enable the video stream when conditions improve.
 *
 * When the remotely subscribed video stream falls back to audio-only or switches back to video, the SDK triggers the `didRemoteSubscribeFallbackToAudioOnly` callback to notify the application of the change.
 *
 * @param option The fallback option for the remotely subscribed video stream. The default value is `BBRtcStreamFallbackOptionVideoStreamLow`. For available options, refer to the BBRtcStreamFallbackOptions enumeration.
 *
 * @return
 * - `0`: Indicates the method call was successful and the fallback option has been set.
 * - A negative value: Indicates a failure to set the fallback option, with specific error codes providing further details if applicable.
 */

// Note: Select an appropriate fallback option to maintain a balance between video quality and robustness of the stream under varying network conditions, especially important for remote subscriptions.
- (int)setRemoteSubscribeFallbackOption:(BBRtcStreamFallbackOptions)option;


#pragma mark Dual-stream Mode

/**-----------------------------------------------------------------------------
 * @name Dual-stream Mode
 * -----------------------------------------------------------------------------
 */

/**
 * Enables or disables dual-stream mode for live broadcast scenarios.
 *
 * When dual-stream mode is enabled, receivers have the option to receive either the high-stream, which offers high-resolution and high-bitrate video, or the low-stream, which provides lower resolution and bitrate.
 *
 * @param enabled A boolean value that sets the stream mode:
 *      - YES: Enables dual-stream mode, allowing the choice between high and low streams.
 *      - NO: (Default) Disables dual-stream mode, using a single stream for all recipients.
 *
 * @return
 * - `0`: Indicates the method call was successful and the stream mode has been set as specified.
 * - A negative value: Indicates a failure to set the stream mode, with specific error codes providing further details if applicable.
 */

// Note: Dual-stream mode is particularly useful in live broadcast settings where different network conditions or user preferences may require alternative video quality options.
- (int)enableDualStreamMode:(BOOL)enabled;

/**
 * Sets the type of the remote user's video stream received by the local user when the remote user sends dual streams.
 *
 * This method enables the application to select the appropriate video stream type based on the size of the video window, allowing for adjustments to optimize bandwidth and resource usage.
 *
 * - If the remote user has enabled dual-stream mode by calling `enableDualStreamMode`, the SDK receives the high-stream video by default. This method can be used to switch to the low-stream video when needed.
 * - If dual-stream mode is not enabled, the SDK still receives the high-stream video by default.
 *
 * The result of this method is returned in the `didApiCallExecute` callback. By default, the high-stream video is used to save bandwidth. Users can switch to the low-stream video using this method if necessary.
 *
 * The low-stream video's aspect ratio is the same as the high-stream video's by default. Once the high-stream video resolution is set, the system automatically configures the resolution, frame rate, and bitrate for the low-stream video accordingly.
 *
 * @param uid The user ID of the remote user sending the video stream.
 * @param streamType The type of video stream to be received. For available stream types, refer to the BBRtcVideoStreamType enumeration.
 *
 * @return
 * - `0`: Indicates the method call was successful and the video stream type has been set.
 * - A negative value: Indicates a failure to set the video stream type, with specific error codes providing further details if applicable.
 */

// Note: Choose the video stream type based on the viewer's network conditions and device capabilities to ensure a balance between video quality and bandwidth consumption.
- (int)setRemoteVideoStream:(NSUInteger)uid
                       type:(BBRtcVideoStreamType)streamType;

/** control Sets the default video-stream type for the video received by the local user when the remote user sends dual streams.

 @param streamType Sets the default video-stream type. See BBRtcVideoStreamType.

 * @return
 * - `0`: Indicates the method call was successful and the stream mode has been set as specified.
 * - A negative value: Indicates a failure to set the stream mode, with specific error codes providing further details if applicable.
 */
- (int)setRemoteDefaultVideoStreamType:(BBRtcVideoStreamType)streamType;


#pragma mark Encryption

/**-----------------------------------------------------------------------------
 * @name Encryption
 * -----------------------------------------------------------------------------
 */

/**
 * Enables built-in encryption with a specified encryption password before joining a channel.
 *
 * All users in the channel must use the same encryption password to ensure mutual encryption and decryption of the audio and video data. The encryption password is automatically cleared when a user leaves the channel.
 *
 * If the encryption password is not specified or is set to an empty string, encryption functionality is disabled, allowing the transmission of unencrypted data.
 *
 * **Note:**
 * - This method is not recommended for use with CDN live streaming scenarios.
 * - To ensure optimal data transmission, make sure that the size of the encrypted data does not exceed the original data size plus 16 bytes. The 16 bytes represent the maximum padding size required for AES encryption.
 *
 * @param secret The encryption password used for encrypting and decrypting the media stream within the channel.
 *
 * @return
 * - `0`: Indicates the method call was successful and the encryption password has been set.
 * - A negative value: Indicates a failure to set the encryption password, with specific error codes providing further details if applicable.
 */

// Note: Use a strong encryption password to protect the privacy and security of the media stream in the channel, keeping in mind the limitations and requirements for encrypted data transmission.
- (int)setEncryptionSecret:(NSString * _Nullable)secret;

/**
 * Sets the built-in encryption mode for the SDK.
 *
 * The SDK supports various encryption modes for securing the media stream. By default, it is set to "aes-128-xts" mode. Use this method to select a different encryption mode if required.
 *
 * All users in the same channel must use the same encryption mode and password to ensure compatibility and proper encryption/decryption of the media stream.
 *
 * For details on the differences between the encryption modes and their implications on security and performance, refer to the AES encryption algorithm documentation.
 *
 * **Note:**
 * - Ensure that the `setEncryptionSecret` method is called to enable the built-in encryption with a password before setting the encryption mode.
 * - This method is not recommended for use with CDN live streaming scenarios.
 *
 * @param encryptionMode The encryption mode to be used for the media stream:
 *     - "aes-128-xts": (Default) 128-bit AES encryption with XTS mode, offering a balance of security and performance.
 *     - "aes-256-xts": 256-bit AES encryption with XTS mode, providing enhanced security.
 *     - "aes-128-ecb": 128-bit AES encryption with ECB mode, which is generally less secure than XTS mode.
 *
 * When `encryptionMode` is set to NULL, the default encryption mode "aes-128-xts" is used.
 *
 * @return
 * - `0`: Indicates the method call was successful and the encryption mode has been set.
 * - A negative value: Indicates a failure to set the encryption mode, with specific error codes providing further details if applicable.
 */

// Note: Choose an encryption mode that meets your security requirements while considering the potential impact on performance and compatibility with other users in the channel.
- (int)setEncryptionMode:(NSString * _Nullable)encryptionMode;


#pragma mark Inject an Online Media Stream

/**-----------------------------------------------------------------------------
 * @name Inject an Online Media Stream
 * -----------------------------------------------------------------------------
 */

/**
 * Adds a voice or video stream RTMP URL address to a live broadcast.
 *
 * The `streamPublishedWithUrl` callback indicates the status of the injected stream.
 * If successful, the server pulls the voice or video stream and injects it into the live channel,
 * allowing all audience members to watch the live content and interact.
 *
 * This method triggers several callbacks:
 * - On the local client:
 *   - `streamInjectedStatusOfUrl` reports the status of the online stream injection.
 *   - `didJoinedOfUid` (uid: 666) if the injection is successful.
 * - On the remote client:
 *   - `didJoinedOfUid` (uid: 666) if the injection is successful.
 *
 * **Note:**
 * - Ensure that the RTMP Converter service is enabled before using this function.
 *   See the [Prerequisites] for the Interactive Broadcast documentation.
 * - This method is available in Native SDK v2.4.1 and later.
 *
 * @param url The URL address to be added to the live broadcast, supporting RTMP, HLS, and FLV protocols.
 * @param config The BBRtcLiveInjectStreamConfig object containing the configuration for the added stream.
 * - For FLV, supported audio codec type is AAC.
 * - For FLV, supported video codec type is H264 (AVC).
 *
 * @return
 * - `0`: Success, indicating the stream URL has been successfully added for injection.
 * - A negative value: Failure, with specific error codes indicating the issue:
 *   - `BBRtcErrorCodeInvalidArgument`(-2): The injected URL does not exist or is invalid.
 *   - `BBRtcErrorCodeNotReady`(-3): The user is not currently in the channel.
 *   - `BBRtcErrorCodeNotSupported`(-4): The channel profile is not set to Live Broadcast.
 *   - `BBRtcErrorCodeNotInitialized`(-7): The SDK is not properly initialized.
 */

// Note: Properly configure the stream URL and ensure the RTMP Converter service is active to successfully inject external media streams into the live channel.
- (int)addInjectStreamUrl:(NSString * _Nonnull)url config:(BBRtcLiveInjectStreamConfig * _Nonnull)config;

/**
 * Removes a voice or video stream RTMP URL address from a live broadcast.
 *
 * Use this method to remove a previously added URL address from a live broadcast session.
 * The URL to be removed should have been previously added via the `addInjectStreamUrl:config:` method.
 *
 * If successful, the SDK triggers the `didOfflineOfUid` callback, indicating that the stream has been removed, and returns a stream uid of 666.
 *
 * @param url The URL address of the stream that was added and is now to be removed from the live broadcast.
 *
 * @return
 * - `0`: Success, indicating the stream URL has been successfully removed from the live broadcast.
 * - A negative value: Failure, with specific error codes providing further details if applicable.
 */

// Note: Properly manage the injection and removal of media streams in live broadcasts to ensure a seamless viewing experience for the audience.
- (int)removeInjectStreamUrl:(NSString * _Nonnull)url;


#pragma mark CDN Live Streaming

/**-----------------------------------------------------------------------------
 * @name CDN Live Streaming
 * -----------------------------------------------------------------------------
 */

/**
 * Publishes the local stream to the CDN for live broadcasting.
 *
 * This method is used to publish the local stream to a CDN, enabling large-scale distribution of the live stream.
 * Upon calling this method, the `rtmpStreamingChangedToState` callback is triggered on the local client to report the state of the operation.
 *
 * **Note:**
 * - This method is designed for use with the live-broadcast profile only.
 * - Ensure that the user has joined the channel before invoking this method.
 * - Make sure to enable the RTMP Converter service beforehand. For more information, see the [Prerequisites] for Interactive Broadcast.
 * - This method can add only one stream URL per invocation.
 *
 * @param url The CDN streaming URL in RTMP format, with a maximum length of 1024 bytes.
 *   The URL must not contain special characters, including non-Latin scripts like Chinese characters.
 * @param transcodingEnabled A boolean value that sets whether transcoding is enabled:
 *   - YES: Enables transcoding, which is useful for processing the audio or video streams when publishing to CDN live.
 *   This is often required for combining the streams of multiple hosts in a live scenario.
 *   If you enable transcoding, make sure to configure the transcoding settings with the `setLiveTranscoding` method before calling this method.
 *   - NO: Disables transcoding.
 *
 * @return
 * - `0`: Success, indicating the local stream has been successfully published to the CDN.
 * - A negative value: Failure, with specific error codes indicating the issue:
 *   - `BBRtcErrorCodeInvalidArgument`(-2): An invalid parameter was provided, such as a nil URL or an empty string.
 *   - `BBRtcErrorCodeNotInitialized`(-7): The RTC Engine has not been initialized when attempting to publish the stream.
 */

// Note: Properly configure the CDN streaming URL and ensure that the RTMP Converter service is active to successfully publish the local stream for live broadcasting.
- (int)addPublishStreamUrl:(NSString * _Nonnull)url transcodingEnabled:(BOOL)transcodingEnabled;

/**
 * Removes an RTMP stream from the CDN live streaming service.
 *
 * This method is used to remove an RTMP URL address that was previously added via the `addPublishStreamUrl:transcodingEnabled:` method from the CDN live stream.
 * When this method is successfully called, the `rtmpStreamingChangedToState` callback is triggered on the local client to report the state of the RTMP stream removal process.
 *
 * **Note:**
 * - This method is exclusively applicable to the live-broadcast profile.
 * - Each invocation of this method can remove only one URL at a time.
 * - The URL should not contain any special characters, including non-Latin scripts like Chinese characters.
 *
 * @param url The RTMP URL address intended for removal from the CDN live stream, with a maximum length of 1024 bytes.
 *
 * @return
 * - `0`: Indicates the method call was successful and the RTMP stream has been removed from the CDN.
 * - A negative value: Indicates a failure to remove the RTMP stream, with specific error codes providing further details if applicable.
 */

// Note: Use this method to manage the RTMP streams in your live broadcast scenarios, ensuring that only the desired streams are published to the CDN.
- (int)removePublishStreamUrl:(NSString * _Nonnull)url;

/**
 * Configures the video layout and audio settings for CDN live streaming.
 *
 * This method is used to set the transcoding options for CDN live streaming, which allows you to customize the video layout and audio settings for the live broadcast.
 * When you call the `setLiveTranscoding` method to update these settings, the SDK triggers the `rtcEngineTranscodingUpdated` callback to indicate that the transcoding settings have been updated.
 *
 * **Note:**
 * - This method is exclusively applicable to the live-broadcast profile.
 * - Ensure that the RTMP Converter service is enabled before using this function. For more information, see the [Prerequisites] for setting up CDN live streaming.
 * - If you are calling the `setLiveTranscoding` method for the first time to update the transcoding settings, the SDK will not trigger the `rtcEngineTranscodingUpdated` callback.
 *
 * @param transcoding The configuration object that sets the audio and video transcoding settings for CDN live streaming. For details on the available settings, refer to BBRtcLiveTranscoding.
 *
 * @return
 * - `0`: Indicates the method call was successful and the transcoding settings have been set.
 * - A negative value: Indicates a failure to set the transcoding settings, with specific error codes providing further details if applicable.
 */

// Note: Proper configuration of the transcoding settings is crucial for achieving the desired video layout and audio experience in CDN live streaming scenarios.
- (int)setLiveTranscoding:(BBRtcLiveTranscoding *_Nullable)transcoding;


#pragma mark Data Stream

/**-----------------------------------------------------------------------------
 * @name Data Stream
 * -----------------------------------------------------------------------------
 */

/**
 * Creates a data stream for sending and receiving data.
 *
 * Each user is allowed to create up to five data streams throughout the lifecycle of the BBRtcEngineKit.
 *
 * **Note:**
 * The `reliable` and `ordered` parameters should be set consistently as either `YES` or `NO` for both. Do not set one to `YES` and the other to `NO`.
 *
 * @param streamId The unique identifier for the created data stream.
 * @param reliable A boolean value that determines the reliability of the data stream delivery:
 *      - YES: The recipients are guaranteed to receive the data stream from the sender within five seconds. If the data is not received within this timeframe, an error is reported to the app.
 *      - NO: There is no guarantee that the data stream will be received within five seconds, and no error is reported for delays or missing data.
 * @param ordered A boolean value that determines whether the data stream is received in the order of transmission:
 *      - YES: The recipients receive the data stream in the order it was sent.
 *      - NO: The order of the received data stream may not match the order in which it was sent.
 *
 * @return
 * - `0`: Indicates the method call was successful and the data stream has been created.
 * - A negative value: Indicates a failure to create the data stream, with specific error codes providing further details if applicable.
 */

// Note: When creating data streams, ensure that the parameters for reliability and ordering are set according to the desired behavior of the data transmission within your application.
- (int)createDataStream:(NSInteger * _Nonnull)streamId
               reliable:(BOOL)reliable
                ordered:(BOOL)ordered;

/**
 * Sends data stream messages to all users in the channel.
 *
 * The SDK imposes certain limitations on the use of this method:
 * - Up to 30 packets can be sent per second within a channel, with each packet not exceeding a maximum size of 1 kB.
 * - Each client is limited to sending up to 6 kB of data per second.
 * - A maximum of five data streams can be active simultaneously per user.
 *
 * Upon successful transmission, the `sendStreamMessage` method triggers the `receiveStreamMessageFromUid` callback on the remote client. This is how the remote user receives the stream message.
 *
 * If the transmission fails, the `sendStreamMessage` method triggers the `didOccurStreamMessageErrorFromUid` callback on the remote client, reporting the error.
 *
 * **Note:**
 * - This method is applicable to the Communication profile and to hosts in the Live-broadcast profile. If an audience member in the Live-broadcast profile uses this method, their role may be upgraded to a host.
 *
 * @param streamId The ID of the data stream being sent, which is returned from the `createDataStream` method.
 * @param data The data to be sent within the data stream.
 *
 * @return
 * - `0`: Indicates the method call was successful and the data has been sent.
 * - A negative value: Indicates a failure to send the data, with specific error codes providing further details if applicable.
 */

// Note: When sending data stream messages, be mindful of the rate and size limitations to ensure successful delivery within the constraints of the SDK.
- (int)sendStreamMessage:(NSInteger)streamId
                    data:(NSData * _Nonnull)data;


#pragma mark Miscellaneous Video Control

/**-----------------------------------------------------------------------------
 * @name Miscellaneous Video Control
 * -----------------------------------------------------------------------------
 */

/**
 * Sets the camera capture preference to optimize performance or preview quality.
 *
 * For video calls or live broadcasts, the SDK typically manages the camera output parameters. However, if the default camera capture settings do not meet special requirements or lead to performance issues, you can use this method to adjust the camera capture behavior:
 * - If the raw video data's resolution or frame rate is higher than the encoder configuration set by `setVideoEncoderConfiguration`, processing video frames may consume extra CPU and RAM resources, leading to performance degradation. In such cases, set the `configuration` to `BBRtcCameraCaptureOutputPreferencePerformance` to prioritize performance.
 * - If local video preview is not required or you are willing to trade off preview quality for better CPU and RAM usage, set the `configuration` to `BBRtcCameraCaptureOutputPreferencePerformance`.
 * - For a higher quality local video preview, set the `configuration` to `BBRtcCameraCaptureOutputPreferencePreview`.
 *
 * **Note:**
 * Call this method before enabling the local camera. It can be called before `joinChannel`, `enableVideo`, or `enableLocalVideo`, depending on the method you use to activate your local camera.
 *
 * @param configuration The camera capturer configuration that determines the balance between performance and preview quality. For available options, refer to BBRtcCameraCapturerConfiguration.
 *
 * @return
 * - `0`: Indicates the method call was successful and the camera capture preference has been set.
 * - A negative value: Indicates a failure to set the camera capture preference, with specific error codes providing further details if applicable.
 */

// Note: Choose the camera capture preference based on the specific needs of your application, considering the trade-offs between performance and preview quality.
- (int)setCameraCapturerConfiguration:(BBRtcCameraCapturerConfiguration * _Nullable)configuration;


#if TARGET_OS_IPHONE
#pragma mark Camera Control

/**-----------------------------------------------------------------------------
 * @name Camera Control
 * -----------------------------------------------------------------------------
 */

/** control Switches between front and rear cameras. (iOS only)

 @return * 0: Success.
* < 0: Failure.
 */
- (int)switchCamera;

- (int)switchCamera2:(BBRtcCameraDirection)direction;

/** control Checks whether the camera zoom function is supported. (iOS only.)

 @return * YES: The device supports the camera zoom function.
 * NO: The device does not support the camera zoom function.
 */
- (BOOL)isCameraZoomSupported;

/** control Checks whether the camera flash function is supported. (iOS only.)

 **Note:**

 The app generally enables the front camera by default. If your front camera flash is not supported, this method returns `NO`. If you want to check if the rear camera flash is supported, call the switchCamera method before calling this method.

 @return * YES: The device supports the camera flash function.
 * NO: The device does not support the camera flash function.
 */
- (BOOL)isCameraTorchSupported;

/** control Checks whether the camera manual focus function is supported. (iOS only)

 @return * YES: The device supports the camera manual focus function.
 * NO: The device does not support the camera manual focus function.
 */
- (BOOL)isCameraFocusPositionInPreviewSupported;

/** control Checks whether the camera manual exposure function is supported. (iOS only)

 @return * YES: The device supports the manual exposure function.
 * NO: The device does not support the manual exposure function.
 */
- (BOOL)isCameraExposurePositionSupported;

/** control Checks whether the camera auto-face focus function is supported. (iOS only)

 @return * YES: The device supports the camera auto-face focus function.
 * NO: The device does not support the camera auto-face focus function.
 */
- (BOOL)isCameraAutoFocusFaceModeSupported;

/** control Sets the camera zoom ratio. (iOS only)

 @param zoomFactor Sets the camera zoom factor. The value ranges between 1.0 and the maximum zoom supported by the device.

 @return * The set camera zoom factor, if this method call is successful.
 * < 0: Failure.
 */
- (CGFloat)setCameraZoomFactor:(CGFloat)zoomFactor;

/** control Sets the manual focus position. (iOS only)

A successful setCameraFocusPositionInPreview method call triggers the o[cameraFocusDidChangedToRect]([BBRtcEngineDelegate rtcEngine:cameraFocusDidChangedToRect:]) callback on the local client.

 @param position Coordinates of the touch point in the view.

 @return * YES: Success.
* NO: Failure.
 */
- (BOOL)setCameraFocusPositionInPreview:(CGPoint)position;

/** control Sets the camera exposure position. (iOS only)

A successful setCameraExposurePosition method call triggers the [cameraExposureDidChangedToRect]([BBRtcEngineDelegate rtcEngine:cameraExposureDidChangedToRect:]) callback on the local client.

 @param positionInView Coordinates of the touch point in the view.

 @return * YES: Success.
 * NO: Failure.
 */
- (BOOL)setCameraExposurePosition:(CGPoint)positionInView;

/** control Enables the camera flash function. (iOS only.)

 @param isOn * YES: Enable the camera flash function.
 * NO: Disable the camera flash function.

 @return * YES: Success.
* NO: Failure.
 */
- (BOOL)setCameraTorchOn:(BOOL)isOn;

/** control Enables the camera auto-face focus function. (iOS only.)

 @param enable * YES: Enable the camera auto-face focus function.
 * NO: (Default) Disable the camera auto-face focus function.

 @return * YES: Success.
* NO: Failure.
 */
- (BOOL)setCameraAutoFocusFaceModeEnabled:(BOOL)enable;

#endif


#if (!(TARGET_OS_IPHONE) && (TARGET_OS_MAC))
#pragma mark Device Manager (macOS)
/**-----------------------------------------------------------------------------
 * @name Device Manager (macOS only)
 * -----------------------------------------------------------------------------
 */

/**
 * Monitors the change of a device state for external audio/video devices on macOS.
 *
 * Use this method to detect when external audio or video devices, such as an external camera, are plugged in or swapped out.
 * This feature is particularly useful for applications that require dynamic handling of connected peripherals.
 *
 * @param enabled A boolean value that determines whether to enable or disable the monitoring of device state changes:
 *      - YES: Enables monitoring, and the application will receive notifications for changes in the connection status of external devices.
 *      - NO: Disables monitoring, stopping the application from receiving notifications about device state changes.
 */

// Note: This method is macOS-specific and can be used to enhance the user experience by providing real-time feedback on the status of external audio/video devices.
- (void)monitorDeviceChange:(BOOL)enabled;

/** Retrieves all devices in the system. (macOS only.)

 **Note:**

 Do not call this method in the main thread.

 This method returns an NSArray object, including all audio/video devices in the system.
 Your app can use the BBRtcDeviceInfo array object to enumerate the devices.

 @param type Device type: BBRtcMediaDeviceType.
 @return An BBRtcDeviceInfo NSArray object including all devices, if this method call is successful.
 */
- (NSArray<BBRtcDeviceInfo *> * _Nullable)enumerateDevices:(BBRtcMediaDeviceType)type;

/**
 * Retrieves a list of all devices in the system for a specified media type. (macOS only)
 *
 * **Note:**
 * - Do not call this method in the main thread to avoid blocking the UI or causing performance issues.
 *
 * This method returns an NSArray of BBRtcDeviceInfo objects, representing all the audio/video devices available in the system.
 * Your application can utilize this array to enumerate and identify the devices according to their properties and capabilities.
 *
 * @param type The type of devices to retrieve, defined by BBRtcMediaDeviceType. This can be used to filter the list to only audio or video devices, or both.
 *
 * @return
 * - An NSArray of BBRtcDeviceInfo objects representing all the devices in the system that match the specified type, if the method call is successful.
 * - `nil` or an empty array if the method fails or there are no devices of the given type available.
 */

// Note: Use this method to obtain a comprehensive list of system devices for management or selection within your application, ensuring to handle the returned data appropriately in a background thread.
- (BBRtcDeviceInfo * _Nullable)getDeviceInfo:(BBRtcMediaDeviceType)type;

/** control Sets the playback, recording, or audio-sampling device. (macOS only.)

 @param type    Device type: BBRtcMediaDeviceType.
 @param deviceId Device ID of the device, which can be retrieved by calling the [enumerateDevices](enumerateDevices:)method. `deviceId` does not change when the device is plugged or unplugged.
 @return * 0: Success.
* < 0: Failure.
 */

- (int)setDevice:(BBRtcMediaDeviceType)type deviceId:(NSString * _Nonnull)deviceId;

/** control Retrieves the specified device's volume. (macOS only.)

 @param type Device type: BBRtcMediaDeviceType.
 @return * Returns the volume, if this method call is successful.

* < 0: Failure.
 */
- (int)getDeviceVolume:(BBRtcMediaDeviceType)type;

/** control Sets the specified device's volume. (macOS only.)

 @param type   Device type: BBRtcMediaDeviceType
 @param volume Sets the specified device's volume. The value ranges between 0 and 100.
 @return * 0: Success.
* < 0: Failure.
 */
- (int)setDeviceVolume:(BBRtcMediaDeviceType)type volume:(int)volume;

/**
 * Initiates a microphone test to verify its functionality. (macOS only)
 *
 * This method is used to check if the microphone is working correctly. Upon starting the test, the SDK provides volume information through the `reportAudioVolumeIndicationOfSpeakers` callback.
 *
 * @param indicationInterval The interval period in milliseconds at which the `reportAudioVolumeIndicationOfSpeakers` callback is triggered, reporting the volume levels.
 *
 * @return
 * - `0`: Indicates the method call was successful and the microphone test has started.
 * - A negative value: Indicates a failure to start the microphone test, with specific error codes providing further details if applicable.
 */

// Note: Utilize this method to perform a diagnostic check on the microphone before starting audio capture in your application, ensuring clear audio input.
- (int)startRecordingDeviceTest:(int)indicationInterval;

/**
 * Stops the microphone test. (macOS only)
 *
 * Use this method to cease the microphone testing process that was initiated by the `startRecordingDeviceTest:` method.
 * It is crucial to call this method to stop the test once the diagnostics or intended testing period is complete.
 *
 * @return
 * - `0`: Indicates the method call was successful and the microphone test has been stopped.
 * - A negative value: Indicates a failure to stop the microphone test, with specific error codes providing further details if applicable.
 */

// Note: Remember to stop the microphone test after completing your diagnostics or test procedures to ensure resources are properly released and the application remains responsive.
- (int)stopRecordingDeviceTest;

/**
 * Initiates an audio playback device test to verify its functionality. (macOS only)
 *
 * This method is used to test if the audio playback device is working correctly using a specified audio file.
 * The test involves playing the audio file, and if the device is functioning properly, you should be able to hear the playback.
 *
 * @param audioFileName The absolute path of the audio file in UTF-8 encoding, with supported file formats including:
 *     - wav
 *     - mp3
 *     - m4a
 *     - aac
 * The supported sample rates for the audio file are:
 *     - 8000 Hz
 *     - 16000 Hz
 *     - 32000 Hz
 *     - 44100 Hz
 *     - 48000 Hz
 *
 * @return
 * - `0`: Indicates the method call was successful, and the playback of the specified audio file can be heard.
 * - A negative value: Indicates a failure to play the audio file, with specific error codes providing further details if applicable.
 */

// Note: Use this method to perform a diagnostic check on the audio playback device to ensure clear audio output. Ensure the audio file meets the supported formats and sample rates for accurate testing.
- (int)startPlaybackDeviceTest:(NSString * _Nonnull)audioFileName;

/**
 * Stops the audio playback device test. (macOS only)
 *
 * Use this method to terminate the testing of the audio playback device that was initiated by the `startPlaybackDeviceTest:` method.
 * It is essential to call this method to stop the test once you have finished verifying the device's functionality.
 *
 * @return
 * - `0`: Indicates the method call was successful, and the audio playback device test has been stopped.
 * - A negative value: Indicates a failure to stop the test, with specific error codes providing further details if applicable.
 */

// Note: Ensure you stop the audio playback device test after completing your diagnostics to free up system resources and prevent unwanted audio output.
- (int)stopPlaybackDeviceTest;

/**
 * Initiates a video-capture device test to verify its functionality. (macOS only)
 *
 * This method is used to check if the video-capture device is working correctly. To perform this test, ensure that you have called the `enableVideo` method beforehand to enable video capabilities, and that the `view` parameter is set to a valid view window for displaying the video feed.
 *
 * @param view The input parameter specifying the view window where the captured video will be displayed. This should be a valid and properly configured view object.
 *
 * @return
 * - `0`: Indicates the method call was successful, and the video-capture device test has started, with the video being displayed in the specified view window.
 * - A negative value: Indicates a failure to start the video-capture device test, with specific error codes providing further details if applicable.
 */

// Note: Use this method to perform a diagnostic check on the video-capture device to ensure proper video input. Make sure the view window is set up correctly to receive and display the video stream.
- (int)startCaptureDeviceTest:(NSView * _Nonnull)view;

/**
 * Stops the video-capture device test. (macOS only)
 *
 * Use this method to terminate the testing of the video-capture device that was initiated by the `startCaptureDeviceTest:` method.
 * It is essential to call this method to stop the test once you have completed the diagnostics or no longer need to use the video-capture device.
 *
 * @return
 * - `0`: Indicates the method call was successful, and the video-capture device test has been stopped.
 * - A negative value: Indicates a failure to stop the test, with specific error codes providing further details if applicable.
 */

// Note: Remember to stop the video-capture device test after your diagnostics to ensure resources are properly released and the application remains in a clean state.
- (int)stopCaptureDeviceTest;

/**
 * Initiates the audio device loopback test to verify the functionality of local audio devices. (macOS only)
 *
 * This method is used to test if the local audio devices, such as the microphone and speaker, are working correctly. When the test is started, the microphone captures local audio, which is then played back through the speaker. The `reportAudioVolumeIndicationOfSpeakers` callback provides the local audio volume information at the specified interval.
 *
 * **Note:**
 * This method assesses the local audio devices and does not provide feedback on network conditions.
 *
 * @param indicationInterval The time interval in milliseconds at which the `reportAudioVolumeIndicationOfSpeakers` callback is triggered to return the local audio volume information. It is recommended to set this value to greater than 200 ms, with the minimum value being 10 ms.
 *
 * @return
 * - `0`: Indicates the method call was successful, and the audio device loopback test has started.
 * - A negative value: Indicates a failure to start the loopback test, with specific error codes providing further details if applicable.
 */

// Note: Utilize this method to perform a diagnostic check on the local audio devices to ensure proper audio capture and playback. Adjust the indicationInterval for optimal test results.
-(int)startAudioDeviceLoopbackTest:(int)indicationInterval;

/**
 * Stops the audio device loopback test. (macOS only)
 *
 * It is important to call this method to cease the loopback testing process that was initiated by the `startAudioDeviceLoopbackTest` method.
 * This ensures that the test is properly concluded and resources are freed after the diagnostics are complete.
 *
 * @return
 * - `0`: Indicates the method call was successful, and the audio device loopback test has been stopped.
 * - A negative value: Indicates a failure to stop the loopback test, with specific error codes providing further details if applicable.
 */

// Note: Remember to terminate the audio loopback test using this method once the testing phase is over to ensure the application remains in a stable state.
-(int)stopAudioDeviceLoopbackTest;
#endif

#pragma mark Custom Media Metadata

/**-----------------------------------------------------------------------------
 * @name Media Metadata
 * -----------------------------------------------------------------------------
 */

/**
 * Sets the data source for metadata to be used in the video stream.
 *
 * To utilize this feature, you must implement the BBRtcMediaMetadataDataSource protocol and define the type of metadata you intend to use.
 * By combining this method with the `setMediaMetadataDelegate:withType:` method, you can add synchronized metadata to the video stream, enhancing live broadcast interactions with features like sending shopping links, digital coupons, and online quizzes.
 *
 * **Note:**
 * - Ensure this method is called before joining the channel with the `joinChannelByToken` method.
 * - This method is designed for use with the live broadcast channel profile only.
 *
 * @param metadataDataSource An object conforming to the BBRtcMediaMetadataDataSource protocol, responsible for providing the metadata to be synchronized with the video stream.
 * @param type The type of metadata to be used. For possible metadata types, refer to the BBRtcMetadataType enumeration. Currently, the SDK supports only video metadata.
 *
 * @return
 * - YES: Indicates the method call was successful and the metadata data source has been set.
 * - NO: Indicates a failure to set the metadata data source, with specific error codes providing further details if applicable.
 */

// Note: Properly configure the metadata data source and delegate to enrich the live broadcast experience with interactive and dynamic content.
- (BOOL)setMediaMetadataDataSource:(id<BBRtcMediaMetadataDataSource> _Nullable) metadataDataSource withType:(BBRtcMetadataType)type;

/**
 * Sets the delegate for handling metadata operations.
 *
 * To use metadata in your application, you must implement the BBRtcMediaMetadataDelegate protocol and specify the type of metadata you want to handle.
 *
 * **Note:**
 * - This method should be called before joining the channel with the `joinChannelByToken` method.
 * - It is designed for use with the live broadcast channel profile only.
 *
 * @param metadataDelegate An object conforming to the BBRtcMediaMetadataDelegate protocol, which is responsible for receiving and processing metadata events.
 * @param type The type of metadata to be handled. For possible metadata types, refer to the BBRtcMetadataType enumeration. Currently, the SDK supports video metadata only.
 *
 * @return
 * - YES: Indicates the method call was successful and the metadata delegate has been set.
 * - NO: Indicates a failure to set the metadata delegate, with specific error codes providing further details if applicable.
 */

// Note: Ensure that the metadata delegate is properly configured to manage metadata in live broadcast scenarios, enhancing the interactivity and user experience of your live streams.
- (BOOL)setMediaMetadataDelegate:(id<BBRtcMediaMetadataDelegate> _Nullable) metadataDelegate withType:(BBRtcMetadataType)type;

#pragma mark Miscellaneous Methods

/**
 * Enables or disables the dispatch of delegate methods to the main queue.
 *
 * This method determines whether delegate methods should be executed on the main queue, which is typically necessary for UI updates.
 * If this feature is disabled, the app must ensure that any UI operations are dispatched to the main queue manually.

 * @param enabled A boolean value that sets the dispatch behavior of delegate methods:
 *      - YES: Delegate methods are dispatched to the main queue, allowing for safe UI updates.
 *      - NO: Delegate methods are not dispatched to the main queue, requiring the app to manage UI updates on the main queue manually.
 *
 * @return
 * - `0`: Indicates the method call was successful and the dispatch setting has been updated.
 * - A negative value: Indicates a failure to update the dispatch setting, with specific error codes providing further details if applicable.
 */

// Note: Consider the implications for UI updates when deciding whether to dispatch delegate methods to the main queue, and ensure that UI-related operations are performed on the main queue to prevent threading issues.
- (int)enableMainQueueDispatch:(BOOL)enabled;

/**
 * Retrieves the version of the SDK.
 *
 * This method provides the version number of the SDK in string format, which can be useful for checking the version of the SDK currently in use.
 *
 * @return The version of the current SDK as a string. For example, "2.3.0"
 */

// Note: Use this method to obtain the version information of the SDK for record-keeping, compatibility checks, or displaying the version in the application's user interface.
+ (NSString * _Nonnull)getSdkVersion;

/**
 * Specifies the output log file for the SDK.
 *
 * The log file captures all operational log data for the SDK. Make sure that the directory where the log file is to be saved exists and is writable.
 *
 * **Note:**
 * - The default log file locations are:
 *     - iOS: `App Sandbox/Library/caches/BBRtcsdk.log`
 *     - macOS:
 *         - Sandbox enabled: `App Sandbox/Library/Logs/BBRtcsdk.log`, for example, `/Users/<username>/Library/Containers/<App Bundle Identifier>/Data/Library/Logs/BBRtcsdk.log`.
 *         - Sandbox disabled: `～/Library/Logs/BBRtcsdk.log`.
 * - It is recommended to call this method right after the `sharedEngineWithAppId:delegate:` method to ensure the completeness of the output log.
 *
 * @param filePath The absolute path of the log file in UTF-8 encoding.
 *
 * @return
 * - `0`: Indicates the method call was successful, and the log file path has been set.
 * - A negative value: Indicates a failure to set the log file path, with specific error codes providing further details if applicable.
 */

// Note: Designate the log file path early in the SDK initialization process to capture logs comprehensively and facilitate debugging and monitoring of the SDK's operation.
- (int)setLogFile:(NSString * _Nonnull)filePath;

/**
 * Sets the output log level for the SDK, determining the types of log messages that are recorded.
 *
 * You can use a single filter or combine multiple filters. The log levels are ordered from the least verbose to the most verbose as follows: OFF, CRITICAL, ERROR, WARNING, INFO, and DEBUG. Selecting a log level will include all logs at that level and below.
 *
 * For example, setting the log level to WARNING will result in logs from levels CRITICAL, ERROR, and WARNING being recorded.
 *
 * @param filter The log filter level that determines which log messages are output. For available log filter levels, refer to the BBRtcLogFilter enumeration.
 *
 * @return
 * - `0`: Indicates the method call was successful, and the log level has been set as specified.
 * - A negative value: Indicates a failure to set the log level, with specific error codes providing further details if applicable.
 */

// Note: Choose an appropriate log level to balance the verbosity of the logs with the needs of your application's debugging and monitoring processes.
- (int)setLogFilter:(NSUInteger)filter;

/**
 * Sets the maximum size of the SDK's log files in kilobytes (KB).
 *
 * The SDK maintains two log files, each with a default size of 512 KB. By setting the `fileSizeInKBytes` parameter, you can adjust the maximum size of these log files. For example, setting `fileSizeInKBytes` to 1024 KB will result in log files with a total maximum size of 2 MB.
 *
 * If the cumulative size of the log files exceeds the specified size, the SDK will manage the log files by overwriting the oldest logs with new log entries.
 *
 * @param fileSizeInKBytes The maximum size of the SDK's log files in kilobytes.
 *
 * @return
 * - `0`: Indicates the method call was successful, and the log file size has been set as specified.
 * - A negative value: Indicates a failure to set the log file size, with specific error codes providing further details if applicable.
 */

// Note: Configure the log file size according to your application's logging needs and storage capabilities to ensure that the log data is neither excessively large nor insufficient for diagnostic purposes.
- (int)setLogFileSize:(NSUInteger)fileSizeInKBytes;

/**
 * Retrieves the native handler of the SDK engine.
 *
 * This interface is provided for special use cases where direct access to the underlying C++ handler of the SDK engine is required. Such scenarios may include registering observers for audio and video frames, which may be necessary for advanced integration or customization purposes.
 *
 * @return The native C++ handler of the SDK engine. The exact type and usage of this handler will depend on the specific requirements of the application and the capabilities exposed by the SDK.
 */

// Note: Accessing the native handler is typically reserved for advanced users or developers who need to leverage additional functionalities provided by the SDK that are not exposed through the standard API interface.
- (void * _Nullable)getNativeHandle;

/** contorl Sets and retrieves the SDK delegate.

 The SDK uses the delegate to inform the app on engine runtime events. All methods defined in the delegate are optional implementation methods.

 */
@property (nonatomic, weak) id<BBRtcEngineDelegate> _Nullable delegate;

#pragma mark Customized Methods (Technical Preview)

/**-----------------------------------------------------------------------------
 * @name Customized Methods (Technical Preview)
 * -----------------------------------------------------------------------------
 */

/**
 * Enables technical preview functionalities or special customizations by configuring the SDK with JSON options.
 *
 * This method allows the application to leverage advanced or experimental features that may not be generally available in the standard SDK interface. It is intended for use cases where specific customizations or access to new features prior to their public release are required.
 *
 * **Note:**
 * The JSON options for SDK configuration are not publicly documented by default. BBRtc is in the process of making commonly used JSON options publicly available in a standardized manner. For more information on these options or to access them, contact BBRtc support.
 *
 * @param options A JSON-formatted string that specifies the SDK options for enabling technical preview functionalities or special customizations. The exact format and available options should be obtained from BBRtc documentation or support.
 */

// Note: Use this method to explore and integrate cutting-edge features or custom settings that are not part of the standard SDK offering. Reach out to BBRtc for guidance on available JSON options and their usage.
- (int)setParameters:(NSString * _Nonnull)options;

/**
 * Retrieves the SDK's parameters for customization purposes.
 *
 * This method is designed to obtain various parameters of the SDK that can be customized to suit specific application requirements or to enable the use of specialized features.
 *
 * **Note:**
 * This method is not publicly documented and may require access to non-public APIs or internal SDK configurations. For more information on how to use this method or to gain access to these parameters, contact BBRtc support.
 *
 * @return A collection of SDK parameters that can be inspected or modified for advanced customization. The format and usage of these parameters should be discussed with BBRtc support to ensure proper integration and functionality.
 */

// Note: Reach out to BBRtc support for guidance on accessing and customizing SDK parameters that are not part of the public API, especially if you require specialized configurations or features.
- (NSString * _Nullable)getParameter:(NSString * _Nonnull)parameter
                                args:(NSString * _Nullable)args;


#pragma mark Deprecated Methods

/**-----------------------------------------------------------------------------
 * @name Deprecated Methods
 * -----------------------------------------------------------------------------
 */

/**
 * Sets the local video display mode.
 *
 * **DEPRECATED** from version 3.0.0, use the [BBRtcEngineKit setupLocalVideo:] method instead.
 *
 * This method can be invoked multiple times during a call to change the display mode.
 *
 * @param mode Sets the local video display mode. See BBRtcVideoRenderMode for details.
 * @return * 0: Success.
 *         * Less than 0: Failure.
 */
- (int)setLocalRenderMode:(BBRtcVideoRenderMode)mode;

/**
 * Sets the remote video display mode.
 *
 * **DEPRECATED** from version 3.0.0, use the [BBRtcEngineKit setupRemoteVideo:] method instead.
 *
 * This method can be invoked multiple times during a call to change the display mode of the remote video.
 *
 * @param uid The user ID of the remote user who is sending the video streams.
 * @param mode Sets the remote video display mode. See BBRtcVideoRenderMode for details.
 * @return * 0: Success.
 *         * Less than 0: Failure.
 */
- (int)setRemoteRenderMode:(NSUInteger)uid
                      mode:(BBRtcVideoRenderMode)mode;

/**
 * Enables interoperability with the BBRtc Web SDK.
 *
 * **Deprecated**: This method is no longer required from version 3.0.0. The Native SDK now automatically ensures compatibility with the Web SDK.
 *
 * - **Live-broadcast Profile**: This method is specifically applicable to the Live-broadcast profile. In this profile, you must explicitly enable interoperability if there are Web SDK users in the channel to avoid black screen issues for the Web users.
 * - **Communication Profile**: Interoperability with the Web SDK is enabled by default, so this method is not needed.
 *
 * @param enabled A boolean value that specifies whether to enable or disable interoperability with the BBRtc Web SDK:
 *   - **YES**: Enables interoperability (only required for Live-broadcast profile with Web SDK users).
 *   - **NO**: (Default) Disables interoperability, not necessary in Communication profile.
 *
 * @return
 *   - **0**: Indicates the operation was successful.
 *   - **Less than 0**: Indicates an error occurred.
 */
- (int)enableWebSdkInteroperability:(BOOL)enabled;
/**
 * Initializes the BBRtcEngineKit object.
 *
 * **Deprecated**: This method has been deprecated since version 2.3. Use the `[BBRtcEngineKit sharedEngineWithAppId:delegate:]` method instead.
 *
 * @see [BBRtcEngineKit sharedEngineWithAppId:delegate:]
 *
 * @param AppId The App ID provided by BBRtc. If you do not have an App ID, you must apply for one from BBRtc. Each project is assigned a unique App ID, which is essential for identifying your project and organization.
 *             The App ID is used in the `[BBRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]` method to access the BBRtc Global Network, facilitating communication in one-to-one or one-to-more scenarios, or live-broadcast sessions.
 *             It is crucial for enabling communication or live sessions using a unique channel name associated with your App ID.
 *
 * @param errorBlock A block that returns an error code of type `BBRtcErrorCode`. This block is invoked in case of an error during the initialization process.
 */
+ (instancetype _Nonnull)sharedEngineWithAppId:(NSString * _Nonnull)AppId
                                         error:(void(^ _Nullable)(BBRtcErrorCode errorCode))errorBlock __deprecated_msg("use sharedEngineWithAppId:delegate: instead.");

/** control Disables the audio function in a channel.

**DEPRECATED** from v2.3

 @see disableAudio
 @return * 0: Success.
* < 0: Failure.
 */
- (int)pauseAudio __deprecated_msg("use disableAudio instead.");

/** control Resumes the audio in a channel.

 **DEPRECATED** from v2.3

 @see enableAudio
 @return * 0: Success.
* < 0: Failure.
 */
- (int)resumeAudio __deprecated_msg("use enableAudio instead.");

/**
 * Sets the high-quality audio parameters.
 *
 * **Deprecated**: This method has been deprecated since version 2.3. Use the `[setAudioProfile:scenario:]` method instead.
 *
 * @param fullband A boolean value that sets whether to enable or disable the full-band codec with a 48 kHz sample rate. This feature is not compatible with versions earlier than 1.7.4.
 * @param stereo A boolean value that sets whether to enable or disable the stereo codec. This feature is not compatible with versions earlier than 1.7.4.
 * @param fullBitrate A boolean value that sets whether to enable or disable high-bitrate mode, which is recommended for voice-only mode.
 *
 * @return
 *   - **0**: Indicates the operation was successful.
 *   - **Less than 0**: Indicates an error occurred.
 */
- (int)setHighQualityAudioParametersWithFullband:(BOOL)fullband
                                          stereo:(BOOL)stereo
                                     fullBitrate:(BOOL)fullBitrate __deprecated_msg("use setAudioProfile:scenario: instead.");

#if (!(TARGET_OS_IPHONE) && (TARGET_OS_MAC))
/** control Sets the speakerphone volume. (macOS only.)

 **DEPRECATED** from v2.3.

 @see [setDeviceVolume](setDeviceVolume:volume:).
 @param volume Sets the speakerphone volume. The value ranges between 0 (lowest volume) and 255 (highest volume).

 @return * 0: Success.
* < 0: Failure.
 */
- (int)setSpeakerphoneVolume:(NSUInteger)volume __deprecated_msg("use setDeviceVolume:volume: instead.");

/**
 * Starts screen sharing. (macOS only.)
 *
 * **Deprecated**: This method has been deprecated since version 2.4. Use the `[BBRtcEngineKit startScreenCaptureByDisplayId:rectangle:parameters:]` or `[BBRtcEngineKit startScreenCaptureByWindowId:rectangle:parameters:]` methods instead.
 *
 * @param windowId Sets the target for screen sharing:
 *   - To share the whole screen, set `windowId` to 0 and `rect` to nil.
 *   - To share a specified window, set `windowId` to a non-zero value. Each window has a unique `windowId`.
 *   - To share a specified region, set `windowId` to 0 and provide a valid `rect`. The region is a part of the whole screen, and you can specify it by implementing your own logic (e.g., dragging the mouse). Currently, sharing a region within a specific window is not supported.
 * @param captureFreq The captured frame rate, which is mandatory. The value must be between 1 fps and 15 fps.
 * @param bitRate The captured bitrate, which affects the quality of the shared screen.
 * @param rect Specifies the region for screen sharing. `rect` is used when `windowId` is set to 0. If `rect` is nil, the whole screen is shared.
 *
 * @return
 *   - **0**: Success.
 *   - **Less than 0**: Failure.
 */
- (int)startScreenCapture:(NSUInteger)windowId
          withCaptureFreq:(NSInteger)captureFreq
                  bitRate:(NSInteger)bitRate
                  andRect:(CGRect)rect __deprecated_msg("use startScreenCaptureByDisplayId or startScreenCaptureByWindowId: instead.");


#endif

/**
 * Sets the video profile for the video stream.
 *
 * **Deprecated**: This method has been deprecated since version 2.3. Consider using the `[setVideoEncoderConfiguration:]` method for more control over the video settings.
 *
 * A video profile includes parameters like resolution, frame rate, and bitrate. If the camera does not support the specified resolution, the SDK selects the nearest supported resolution while maintaining the encoder resolution set by `setVideoProfile`.
 *
 * **Important**: Set the video profile according to the following guidelines:
 * - Set the video profile after calling `[enableVideo]`.
 * - Set the video profile before calling `[BBRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]` or `[startPreview]`.
 * - If no further adjustments to the video profile are needed post channel join, set it before `enableVideo` to minimize the render time of the first video frame.
 *
 * @see [BBRtcEngineKit setVideoEncoderConfiguration:]
 * @param profile The video profile to set. See `BBRtcVideoProfile` for available options.
 * @param swapWidthAndHeight A boolean value that determines if the width and height of the video should be swapped:
 *   - **YES**: Swap width and height for portrait mode video.
 *   - **NO**: (Default) Do not swap, maintaining landscape mode video.
 *
 * The output video dimensions will align with the chosen video profile settings.
 *
 * @return
 *   - **0**: Indicates the operation was successful.
 *   - **Less than 0**: Indicates an error occurred.
 */
- (int)setVideoProfile:(BBRtcVideoProfile)profile
    swapWidthAndHeight:(BOOL)swapWidthAndHeight __deprecated_msg("use setVideoEncoderConfiguration: instead.");

/**
 * Manually sets the video encoding profile.
 *
 * **Deprecated**: This method has been deprecated since version 2.3. It is recommended to use the `[setVideoEncoderConfiguration:]` method for setting the video encoding parameters.
 *
 * If you do not intend to change the video profile after joining the channel, it is advised to call this method prior to `[enableVideo]` to reduce the render time of the first video frame.
 *
 * @see [BBRtcEngineKit setVideoEncoderConfiguration:]
 * @param size The size of the video, with the maximum supported resolution being 1280x720.
 * @param frameRate The frame rate of the video, which can be set to values such as 5, 10, 15, 24, or 30 fps. The maximum supported frame rate is 30 fps.
 * @param bitrate The bitrate of the video, which needs to be calculated based on the width, height, and frame rate. For detailed guidance, refer to the bitrate table in `BBRtcVideoEncoderConfiguration`. The bitrate adjustments for different frame rates are as follows:
 *   - At 5 fps, use half of the recommended bitrate.
 *   - At 15 fps, use the recommended bitrate.
 *   - At 30 fps, use 1.5 times the recommended bitrate.
 *   Adjust the bitrate proportionally for other frame rates.
 *
 * **Example**: For a resolution of 320x240 with a frame rate of 15 fps, the bitrate would be 200. Adjust the bitrate as follows for different frame rates:
 *   - At 5 fps, the bitrate would be 100.
 *   - At 30 fps, the bitrate would be 300.
 *
 * If a bitrate is set beyond the appropriate range, the SDK will automatically adjust it to a value within the acceptable range.
 */
- (int)setVideoResolution:(CGSize)size andFrameRate:(NSInteger)frameRate bitrate:(NSInteger)bitrate __deprecated_msg("use setVideoEncoderConfiguration: instead.");

/** contorl Retrieves the device type; such as a recording, playback, or video-capture device. (macOS only.)

 **DEPRECATED**  from v2.3.

 @see [getDeviceInfo](getDeviceInfo:).
 @param type Device type: BBRtcMediaDeviceType.
 @return * Returns the device ID of the device, if this method call is successful.
 * nil: Failure.
 */
- (NSString * _Nullable)getDeviceId:(BBRtcMediaDeviceType)type __deprecated_msg("use getDeviceInfo: instead.");

/**
 * Plays a specified audio effect.
 *
 * **Deprecated**: This method has been deprecated since version 2.3. Use the `[playEffect:filePath:loopCount:pitch:pan:gain:publish:]` method instead.
 *
 * @param soundId The unique identifier for the audio effect. Ensure that if you have preloaded the audio effect using the `[BBRtcEngineKit preloadEffect:filePath:]` method, the `soundId` matches the one set during preloading.
 * @param filePath The absolute file path to the audio effect.
 * @param loopCount The number of times the audio effect should loop:
 *   - **0**: Play the effect once.
 *   - **1**: Play the effect twice.
 *   - **-1**: Loop the effect indefinitely until stopped by `[BBRtcEngineKit stopEffect:]` or `[BBRtcEngineKit stopAllEffects:]`.
 * @param pitch Adjusts the pitch of the audio effect, with a range from 0.5 to 2. The default is 1 (no pitch change), where lower values indicate a lower pitch.
 * @param pan Sets the stereo position of the audio effect from -1.0 (left) to 1.0 (right), with 0.0 indicating the center.
 * @param gain Sets the volume of the audio effect, with a range from 0.0 (silent) to 100.0 (default volume). Lower values result in quieter playback.
 *
 * @return
 *   - **0**: Indicates the operation was successful.
 *   - **Less than 0**: Indicates an error occurred.
 */
- (int)playEffect:(int)soundId
         filePath:(NSString * _Nullable)filePath
        loopCount:(int)loopCount
            pitch:(double)pitch
              pan:(double)pan
             gain:(double)gain ;

/** control Returns the media engine version.

 **DEPRECATED** from v2.3.

 @see getSdkVersion

 @return The media engine version in the string format.
 */
+ (NSString * _Nonnull)getMediaEngineVersion __deprecated;


#pragma mark Deprecated Blocks

/**-----------------------------------------------------------------------------
 * @name Deprecated Blocks
 * -----------------------------------------------------------------------------
 */

/**
 * Reports active speakers and their volume levels.
 *
 * **Deprecated**: This callback has been deprecated since version 1.1. Use the `[BBRtcEngineDelegate rtcEngine:reportAudioVolumeIndicationOfSpeakers:totalVolume:]` delegate method instead.
 *
 * To enable this feature, call the `enableAudioVolumeIndication` method. The callback provides information about the current speakers and their volumes.
 *
 * @param audioVolumeIndicationBlock A block containing the following details:
 *   - speakers: An array of dictionaries, each representing a speaker with their `uid` and `volume`:
 *     - **uid**: The unique identifier for the speaker. If `uid` is 0, it refers to the local user, and the reported volume is the `totalVolume`.
 *     - **volume**: The volume level of the speaker, ranging from 0 (silent) to 255 (loudest).
 *   - totalVolume: The combined volume level after audio mixing, also ranging from 0 to 255.
 *
 * Note: If a `uid` is absent in the current callback compared to the previous one, it indicates that the user did not speak during the latest interval.
 *
 * @see [BBRtcEngineKit enableAudioVolumeIndication]
 */
- (void)audioVolumeIndicationBlock:(void(^ _Nullable)(NSArray * _Nonnull speakers, NSInteger totalVolume))audioVolumeIndicationBlock __deprecated_msg("use delegate instead.");

/** Occurs when the first remote video frame is rendered.

 **DEPRECATED** from v1.1.

 @see [firstRemoteVideoDecodedOfUid]([BBRtcEngineDelegate rtcEngine:firstRemoteVideoDecodedOfUid:size:elapsed:])

 @param firstRemoteVideoFrameBlock This block includes the:

 - uid:     User ID of the remote user sending the video streams.
 - width:   Width (pixels) of the video stream.
 - height:  Height (pixels) of the video stream.
 - elapsed: Time elapsed (ms) from the local user calling [joinChannelByToken]([BBRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) until the SDK triggers this callback.
 */
- (void)firstLocalVideoFrameBlock:(void(^ _Nullable)(NSInteger width, NSInteger height, NSInteger elapsed))firstLocalVideoFrameBlock __deprecated_msg("use delegate instead.");

/** Occurs when the first remote video frame is rendered.

 **DEPRECATED** from v1.1.

 @see [firstRemoteVideoDecodedOfUid]([BBRtcEngineDelegate rtcEngine:firstRemoteVideoDecodedOfUid:size:elapsed:])

 @param firstRemoteVideoFrameBlock This block includes the:

 - uid:     User ID of the remote user sending the video streams.
 - width:   Width (pixels) of the video stream.
 - height:  Height (pixels) of the video stream.
 - elapsed: Time elapsed (ms) from the local user calling [joinChannelByToken]([BBRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) until the SDK triggers this callback.
 */
- (void)firstRemoteVideoDecodedBlock:(void(^ _Nullable)(NSUInteger uid, NSInteger width, NSInteger height, NSInteger elapsed))firstRemoteVideoDecodedBlock __deprecated_msg("use delegate instead.");

/** Occurs when the first remote video frame is rendered.

 **DEPRECATED** from v1.1.

 @see [firstRemoteVideoDecodedOfUid]([BBRtcEngineDelegate rtcEngine:firstRemoteVideoDecodedOfUid:size:elapsed:])

 @param firstRemoteVideoFrameBlock This block includes the:

 - uid:     User ID of the remote user sending the video streams.
 - width:   Width (pixels) of the video stream.
 - height:  Height (pixels) of the video stream.
 - elapsed: Time elapsed (ms) from the local user calling [joinChannelByToken]([BBRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) until the SDK triggers this callback.
 */
- (void)firstRemoteVideoFrameBlock:(void(^ _Nullable)(NSUInteger uid, NSInteger width, NSInteger height, NSInteger elapsed))firstRemoteVideoFrameBlock __deprecated_msg("use delegate instead.");

/**
 * Triggered when a user joins a channel.
 *
 * **Deprecated**: This callback has been deprecated since version 1.1. Use the `[BBRtcEngineDelegate rtcEngine:didJoinedOfUid:elapsed:]` delegate method instead.
 *
 * If there are other users in the channel when this user joins, the SDK reports their presence to the app.
 *
 * @param userJoinedBlock This block includes information about the user who has joined the channel:
 *   - **uid**: The User ID of the user joining the channel. If a `uid` is specified in the `[BBRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]` method, that specific user ID is returned. Otherwise, if the `uid` is not specified, the server automatically assigns one.
 *   - **elapsed**: The time elapsed in milliseconds from when the user calls `[BBRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]` until the SDK triggers this callback, indicating the user has successfully joined the channel.
 */
- (void)userJoinedBlock:(void(^ _Nullable)(NSUInteger uid, NSInteger elapsed))userJoinedBlock __deprecated_msg("use delegate instead.");

/**
 * Triggered when a user joins a channel.
 *
 * **Deprecated**: This callback has been deprecated since version 1.1. Use the `[BBRtcEngineDelegate rtcEngine:didJoinedOfUid:elapsed:]` delegate method instead.
 *
 * If there are other users in the channel when this user joins, the SDK reports their presence to the app.
 *
 * @param userJoinedBlock This block includes information about the user who has joined the channel:
 *   - **uid**: The User ID of the user joining the channel. If a `uid` is specified in the `[BBRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]` method, that specific user ID is returned. Otherwise, if the `uid` is not specified, the server automatically assigns one.
 *   - **elapsed**: The time elapsed in milliseconds from when the user calls `[BBRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]` until the SDK triggers this callback, indicating the user has successfully joined the channel.
 */
- (void)userOfflineBlock:(void(^ _Nullable)(NSUInteger uid))userOfflineBlock __deprecated_msg("use delegate instead.");

/**
 * Triggered when a remote user's audio stream is muted or unmuted.
 *
 * **Deprecated**: This callback has been deprecated since version 1.1. Use the `[BBRtcEngineDelegate rtcEngine:didAudioMuted:byUid:]` delegate method instead.
 *
 * @param userMuteAudioBlock This block includes the following details about the remote user's audio state:
 *   - **uid**: The user ID of the remote user whose audio stream has been affected.
 *   - **muted**: The new state of the remote user's audio stream, indicating whether it is now muted or unmuted:
 *     - **YES**: The audio stream is now muted.
 *     - **NO**: The audio stream is now unmuted.
 */
- (void)userMuteAudioBlock:(void(^ _Nullable)(NSUInteger uid, BOOL muted))userMuteAudioBlock __deprecated_msg("use delegate instead.");

/**
 * Triggered when a remote user's audio stream is muted or unmuted.
 *
 * **Deprecated**: This callback has been deprecated since version 1.1. Use the `[BBRtcEngineDelegate rtcEngine:didAudioMuted:byUid:]` delegate method instead.
 *
 * @param userMuteAudioBlock This block includes the following details about the remote user's audio state:
 *   - **uid**: The user ID of the remote user whose audio stream has been affected.
 *   - **muted**: The new state of the remote user's audio stream, indicating whether it is now muted or unmuted:
 *     - **YES**: The audio stream is now muted.
 *     - **NO**: The audio stream is now unmuted.
 */
- (void)userMuteVideoBlock:(void(^ _Nullable)(NSUInteger uid, BOOL muted))userMuteVideoBlock __deprecated_msg("use delegate instead.");

/**
 * Reports the statistics of the uploading local video streams once every two seconds.
 *
 * **Deprecated**: This callback has been deprecated since version 1.1. Use the `[BBRtcEngineDelegate rtcEngine:localVideoStats:]` delegate method instead.
 *
 * @param localVideoStatBlock This block includes statistics about the local video stream being sent:
 *   - **sentBitrate**: The bitrate of the local video stream sent since the last statistics update, measured in bits per second.
 *   - **sentFrameRate**: The frame rate of the local video stream sent since the last statistics update, measured in frames per second.
 */
- (void)localVideoStatBlock:(void(^ _Nullable)(NSInteger sentBitrate, NSInteger sentFrameRate))localVideoStatBlock __deprecated_msg("use delegate instead.");

/**
 * Reports the statistics of the receiving remote video streams once every two seconds.
 *
 * **Deprecated**: This callback has been deprecated since version 1.1. Use the `[BBRtcEngineDelegate rtcEngine:remoteVideoStats:]` delegate method instead.
 *
 * @param remoteVideoStatBlock This block includes statistics about the remote video streams received:
 *   - **uid**: User ID of the remote user who is sending the video streams.
 *   - **delay**: Time delay of the video stream in milliseconds, indicating the end-to-end latency.
 *   - **receivedBitrate**: The bitrate of the video stream received since the last statistics update, measured in bits per second.
 *   - **decoderOutputFrameRate**: The frame rate at which the video stream is decoded, measured in frames per second since the last count.
 *   - **rendererOutputFrameRate**: The frame rate at which the video stream is rendered, measured in frames per second since the last count.
 */
- (void)remoteVideoStatBlock:(void(^ _Nullable)(NSUInteger uid, NSInteger delay, NSInteger receivedBitrate, NSInteger decoderOutputFrameRate, NSInteger rendererOutputFrameRate))remoteVideoStatBlock __deprecated_msg("use delegate instead.");

/**
 * Reports the statistics of the receiving remote audio streams once every two seconds.
 *
 * **Deprecated**: This callback has been deprecated since version 1.1. Use the `[BBRtcEngineDelegate rtcEngine:remoteAudioStats:]` delegate method instead.
 *
 * @param remoteAudioStatBlock This block includes statistics about the remote audio streams received:
 *   - **uid**: User ID of the user sending the audio streams.
 *   - **quality**: The quality of the received audio for the user, indicating the perceived audio quality.
 *   - **networkTransportDelay**: The network delay from the sender to the receiver, measured in milliseconds.
 *   - **jitterBufferDelay**: The delay introduced by the jitter buffer at the receiver, measured in milliseconds, to compensate for network jitter.
 *   - **audioLossRate**: The audio frame loss rate during the reported interval, expressed as a percentage.
 */
- (void)remoteAudioStatBlock:(void(^ _Nullable)(NSUInteger uid, NSInteger quality, NSInteger networkTransportDelay, NSInteger jitterBufferDelay, NSInteger audioLossRate))remoteAudioStatBlock __deprecated_msg("use delegate instead.");

/** Reports when the camera turns on and is ready to capture the video.

 **DEPRECATED** from v1.1.

 @see [rtcEngineCameraDidReady]([BBRtcEngineDelegate rtcEngineCameraDidReady:])
 */
- (void)cameraReadyBlock:(void(^ _Nullable)(void))cameraReadyBlock __deprecated_msg("use delegate instead.");

/** Reports when the connection between the SDK and the server is lost.

 **DEPRECATED** from v1.1.

 @see [rtcEngineConnectionDidInterrupted]([BBRtcEngineDelegate rtcEngineConnectionDidInterrupted:])
 @see [rtcEngineConnectionDidLost]([BBRtcEngineDelegate rtcEngineConnectionDidLost:])
 */
- (void)connectionLostBlock:(void(^ _Nullable)(void))connectionLostBlock __deprecated_msg("use delegate instead.");

/**
 * Triggered when a user successfully rejoins the channel after a network disconnection.
 *
 * When the client loses connection with the server due to network issues, the SDK will automatically attempt to reconnect. Upon reconnection, this callback is triggered.
 *
 * **Deprecated**: This callback has been deprecated since version 1.1. Use the `[BBRtcEngineDelegate rtcEngine:didRejoinChannel:withUid:elapsed:]` delegate method instead.
 *
 * @param rejoinChannelSuccessBlock A block that includes details about the successful rejoining of the channel:
 *   - **channel**: The name of the channel to which the user has rejoined.
 *   - **uid**: The User ID of the user who rejoined the channel.
 *   - **elapsed**: The time elapsed in milliseconds from the initiation of the reconnection attempt until the callback is triggered, indicating the duration of the reconnection process.
 */
- (void)rejoinChannelSuccessBlock:(void(^ _Nullable)(NSString * _Nonnull channel, NSUInteger uid, NSInteger elapsed))rejoinChannelSuccessBlock __deprecated_msg("use delegate instead.");

/** Reports the RtcEngine runtime statistics once every two seconds.

 **DEPRECATED** from v1.1.

 @see [reportRtcStats]([BBRtcEngineDelegate rtcEngine:reportRtcStats:])
 @param rtcStatsBlock RtcEngine runtime statistics. See [BBRtcChannelStats](BBRtcChannelStats).
 */
- (void)rtcStatsBlock:(void(^ _Nullable)(BBRtcChannelStats * _Nonnull stat))rtcStatsBlock __deprecated_msg("use delegate instead.");

/**
 * Triggered when a user leaves a channel.
 *
 * **Deprecated**: This callback has been deprecated since version 1.1. Use the `[BBRtcEngineDelegate rtcEngine:didLeaveChannelWithStats:]` delegate method instead.
 *
 * When the app calls the `[BBRtcEngineKit leaveChannel:]` method, the SDK utilizes this callback to notify the app of the user's departure from the channel.
 *
 * Through this callback, the app can retrieve information such as call duration and statistics of the received/transmitted data via the `[BBRtcEngineDelegate rtcEngine:audioQualityOfUid:quality:delay:lost:]` callback.
 *
 * @param leaveChannelBlock Contains statistics of the call. For more details, see [BBRtcChannelStats][^31^].
 */
- (void)leaveChannelBlock:(void(^ _Nullable)(BBRtcChannelStats * _Nonnull stat))leaveChannelBlock __deprecated_msg("use delegate instead.");

/**
 * Reports the audio quality of the current call once every two seconds.
 *
 * **Deprecated**: This callback has been deprecated since version 1.1. Use the `[BBRtcEngineDelegate rtcEngine:audioQualityOfUid:quality:delay:lost:]` delegate method instead.
 *
 * @param audioQualityBlock This block includes details about the audio quality:
 *   - **uid**: User ID of the speaker in the call.
 *   - **quality**: Represents the audio quality metrics for the user, using the `BBRtcNetworkQuality` enum.
 *   - **delay**: The time delay of the audio stream in milliseconds.
 *   - **lost**: The audio packet loss rate, expressed as a percentage.
 */
- (void)audioQualityBlock:(void(^ _Nullable)(NSUInteger uid, BBRtcNetworkQuality quality, NSUInteger delay, NSUInteger lost))audioQualityBlock __deprecated_msg("use delegate instead.");

/**
 * Reports the network quality of a specified user in the Communication or Live Broadcast profile once every two seconds.
 *
 * **Deprecated**: This callback has been deprecated since version 1.1. Use the `[BBRtcEngineDelegate rtcEngine:networkQuality:txQuality:rxQuality:]` delegate method instead.
 *
 * @param networkQualityBlock This block includes details about the network quality:
 *   - **uid**: User ID. The network quality reported pertains to the user with this `uid`. If `uid` is 0, it reports the local network quality.
 *   - **txQuality**: The transmission quality of the user, using the `BBRtcNetworkQuality` enum to indicate the upstream network condition.
 *   - **rxQuality**: The receiving quality of the user, using the `BBRtcNetworkQuality` enum to indicate the downstream network condition.
 */
- (void)networkQualityBlock:(void(^ _Nullable)(NSUInteger uid, BBRtcNetworkQuality txQuality, BBRtcNetworkQuality rxQuality))networkQualityBlock __deprecated_msg("use delegate instead.");

/**
 * Reports the last mile network quality of the local user once every two seconds before joining a channel.
 *
 * Last mile refers to the connection between the local device and the BBRtc edge server. After the app calls the `[BBRtcEngineKit enableLastmileTest]` method, this callback provides periodic updates on the uplink and downlink last mile network conditions of the local user prior to joining a channel.
 *
 * @param lastmileQualityBlock This block reports the network quality:
 *   - **Network Quality**: The last mile network quality, which can be one of the following values from the `BBRtcNetworkQuality` enum:
 *     - BBRtcNetworkQualityUnknown
 *     - BBRtcNetworkQualityExcellent
 *     - BBRtcNetworkQualityGood
 *     - BBRtcNetworkQualityModerate
 *     - BBRtcNetworkQualityPoor
 *     - BBRtcNetworkQualityBad
 *     - BBRtcNetworkQualityVBad
 *     - BBRtcNetworkQualityDown
 *     This provides an indication of the local network conditions for both uplink and downlink.
 */
- (void)lastmileQualityBlock:(void(^ _Nullable)(BBRtcNetworkQuality quality))lastmileQualityBlock __deprecated_msg("use delegate instead.");

/** Reports a media engine event.

 **DEPRECATED** from v1.1.
 */
- (void)mediaEngineEventBlock:(void(^ _Nullable)(NSInteger code))mediaEngineEventBlock __deprecated_msg("use delegate instead.");

- (int)setDumpOutputDirectory:(NSString* _Nullable)dir;
- (int)enableDump:(BOOL)enabled;

- (int) setAudioEffectPreset:(BBRtcAudioEffectPreset)preset;

- (int) setVoiceBeautifierPreset:(BBRtcVoiceBeautifierPreset)preset;

- (id<BBRtcAudioDataFrameProtocol> _Nullable) getAudioDelegate;
- (id<BBRtcVideoDataFrameProtocol> _Nullable) getVideoDelegate;
- (id<BBRtcVideoSourceProtocol> _Nullable) getVideoSourceDelegate;

- (void) destoryVideoSourceDelegate;

- (int)setLowlightEnhanceOptions:(BOOL)enable options:(BBRtcLowlightEnhanceOptions* _Nullable)options;

- (int)getVoiceDuration;
@end
