#ifndef MS_RTC_RTP_PROBATION_GENERATOR_HPP
#define MS_RTC_RTP_PROBATION_GENERATOR_HPP

#include "common.hpp"
#include "RTC/RtpPacket.hpp"

namespace RTC
{
	// SSRC of the probation RTP stream.
	constexpr uint32_t RtpProbationSsrc{ 1234u };
	// Codec payload type of the probation RTP stream.
	constexpr uint8_t RtpProbationCodecPayloadType{ 127u };

	class RtpProbationGenerator
	{
		// Custom deleter for RtpPacket unique_ptr.
		struct Deleter
		{
			// Called by unique_ptr to destroy/free the Packet.
			void operator()(RTC::RtpPacket* packet)
			{
				packet->ReturnToPool();
			}
		};

	public:
		explicit RtpProbationGenerator();
		virtual ~RtpProbationGenerator();

	public:
		RTC::RtpPacket* GetNextPacket(size_t size);

	private:
		// Allocated by this.
		uint8_t* probationPacketBuffer{ nullptr };
		std::unique_ptr<RTC::RtpPacket, Deleter> probationPacket{ nullptr };
	}; // namespace RTC

} // namespace RTC

#endif
