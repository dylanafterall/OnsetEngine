// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_audio_manager.h
//  implementation of AudioManager class, for use of OpenAL sound functionality
// -----------------------------------------------------------------------------

#include "core_audio_manager.h"

AudioManager::AudioManager() {
	p_ALCDevice = alcOpenDevice(nullptr); // nullptr = get default device
	if (!p_ALCDevice) {ONSET_ERROR("Failed to get ALC sound device");}

	p_ALCContext = alcCreateContext(p_ALCDevice, nullptr);  // create context
	if(!p_ALCContext) {ONSET_ERROR("Failed to set ALC sound context");}

	if (!alcMakeContextCurrent(p_ALCContext)) {
        ONSET_ERROR("Failed to make ALC Context current");
    }

	const ALCchar* name = nullptr;
	if (alcIsExtensionPresent(p_ALCDevice, "ALC_ENUMERATE_ALL_EXT")) {
        name = alcGetString(p_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
    }
	if (!name || alcGetError(p_ALCDevice) != AL_NO_ERROR) {
        name = alcGetString(p_ALCDevice, ALC_DEVICE_SPECIFIER);
    }
	printf("Opened \"%s\"\n", name);
}

AudioManager::~AudioManager()
{
	if (!alcMakeContextCurrent(nullptr)) {
        ONSET_ERROR("Failed to set ALC Context to nullptr");
    }

	alcDestroyContext(p_ALCContext);
	if (p_ALCContext) {
        ONSET_ERROR("Failed to unset ALC Context during close");
    }

	if (!alcCloseDevice(p_ALCDevice)) {
        ONSET_ERROR("Failed to close the ALC sound device");
    }
}

void AudioManager::setSoundEffect(const std::string& assetID, const char* filename) {
	ALenum err, format;
	ALuint buffer;
	SNDFILE* sndfile;
	SF_INFO sfinfo;
	short* membuf;
	sf_count_t num_frames;
	ALsizei num_bytes;

	/* Open the audio file and check that it's usable. */
	sndfile = sf_open(filename, SFM_READ, &sfinfo);
	if (!sndfile) {
		fprintf(stderr, "Could not open audio in %s: %s\n", filename, sf_strerror(sndfile));
		return;
	}
	if (sfinfo.frames < 1 || sfinfo.frames >(sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels) {
		fprintf(stderr, "Bad sample count in %s (%" PRId64 ")\n", filename, sfinfo.frames);
		sf_close(sndfile);
		return;
	}

	/* Get the sound format, and figure out the OpenAL format */
	format = AL_NONE;
	if (sfinfo.channels == 1) {
		format = AL_FORMAT_MONO16;
	}
	else if (sfinfo.channels == 2) {
		format = AL_FORMAT_STEREO16;
	}
	else if (sfinfo.channels == 3) {
		if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) {
			format = AL_FORMAT_BFORMAT2D_16;
		}
	}
	else if (sfinfo.channels == 4) {
		if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) {
			format = AL_FORMAT_BFORMAT3D_16;
		}
	}
	if (!format) {
		fprintf(stderr, "Unsupported channel count: %d\n", sfinfo.channels);
		sf_close(sndfile);
		return;
	}

	/* Decode the whole audio file to a buffer. */
	membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

	num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
	if (num_frames < 1) {
		free(membuf);
		sf_close(sndfile);
		fprintf(stderr, "Failed to read samples in %s (%" PRId64 ")\n", filename, num_frames);
		return;
	}
	num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

	/* Buffer the audio data into a new buffer object, then free the data and
	 * close the file.
	 */
	buffer = 0;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

	free(membuf);
	sf_close(sndfile);

	/* Check if an error occured, and clean up if so. */
	err = alGetError();
	if (err != AL_NO_ERROR) {
		fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
		if (buffer && alIsBuffer(buffer))
			alDeleteBuffers(1, &buffer);
		return;
	}

	ONSET_INFO("New sound effect added to Audio Manager with id = {}", assetID);
	m_soundEffectBuffers.emplace(assetID, buffer);  // add to the list of known buffers
}

ALuint AudioManager::getSoundEffect(const std::string& assetId) {
    return m_soundEffectBuffers[assetId];
}

void AudioManager::deleteBuffers() {
	for (auto buffer : m_soundEffectBuffers) {
        alDeleteBuffers(1, &buffer.second);
    }
    m_soundEffectBuffers.clear();
}