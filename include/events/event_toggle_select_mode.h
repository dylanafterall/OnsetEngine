// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// event_toggle_select_mode.h
//  header for event: toggling select mode on/off
// -----------------------------------------------------------------------------
#ifndef EVENT_TOGGLE_SELECT_MODE_H
#define EVENT_TOGGLE_SELECT_MODE_H

/** 
 * \brief   The ToggleSelectModeEvent struct.
 * \details Used by EnTT dispatcher to signal that the game's player wants to 
 *          toggle the player entity's select-mode status. If previously on, 
 *          change to off. If previously off, change to on.
 */
struct ToggleSelectModeAudioEvent {
    /**
     * \brief   ID only used for constructing struct. 
     */
    int m_id;
};

#endif // EVENT_TOGGLE_SELECT_MODE_H