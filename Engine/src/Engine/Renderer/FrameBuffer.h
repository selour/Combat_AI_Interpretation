#pragma once
#include <memory>
namespace Engine
{
	struct FrameBufferSpecification
	{
		unsigned int Width, Height;
	};
	class FrameBuffer
	{
	public: 

		virtual void Bind() = 0;
		virtual void UnBind() = 0;


		virtual void BindColorAttachment(unsigned slot = 0) const = 0;

		virtual const unsigned int GetColorAttachment() const = 0;


		virtual const FrameBufferSpecification& GetSpecification() const = 0;

		static std::shared_ptr<FrameBuffer> Create(const FrameBufferSpecification& spec);
	};	
	class MRTFrameBuffer
	{
	public:

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void BindColorAttachment(unsigned slot = 0) const = 0;
		virtual void BindColorAttachment(unsigned slot , unsigned index ) const = 0;
		
		virtual const unsigned int GetColorAttachmentSize() const = 0;

		virtual const FrameBufferSpecification& GetSpecification() const = 0;

		static std::shared_ptr<MRTFrameBuffer> Create(const FrameBufferSpecification& spec, unsigned amount);
	};
}


