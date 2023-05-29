#pragma once
#include <memory>
namespace Engine
{
	enum TextureInternalFormat
	{
		RGB4 = 0,
		RGB5 = 1,
		RGB8 = 2,
		RGB10 = 3,
		RGB12 = 4,
		RGB16 = 5,
		RGBA2 = 6,
		RGBA4 = 7,
		RGB5A1 = 8,
		RGBA8 = 9,
		RGB10A2 = 10,
		RGBA12 = 11,
		RGBA16 = 12,
		RGBA32F = 13,
		RGB32F = 14,
		RGBA16F = 15,
		RGB16F = 16
	};
	enum TextureFormat
	{
		RED = 0,
		GREEN = 1,
		BLUE = 2,
		ALPHA = 3,
		RGB = 4,
		RGBA = 5
	};
	enum TextureFilter
	{
		NEAREST = 0,
		LINEAR = 1
	}; 
	enum TextureWrap
	{
		REPEAT = 0,
		MIRRORED_REPEAT = 1,
		CLAMP_TO_EDGE = 2
	};
	struct ColorAttachmentSpecification
	{
		unsigned int Width, Height;
		TextureInternalFormat InternalFormat;
		TextureFormat Format;
		TextureFilter Filter;
		TextureWrap Wrap;

	};
	struct RenderBufferSpecification
	{
		unsigned int Width, Height;

	};

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


		virtual const ColorAttachmentSpecification& GetColorAttachmentSpec() const = 0;

		static std::shared_ptr<FrameBuffer> Create(const ColorAttachmentSpecification& spec);
		static std::shared_ptr<FrameBuffer> Create(const ColorAttachmentSpecification& cas, const RenderBufferSpecification& rbs);
	};	
	class MRTFrameBuffer
	{
	public:

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void BindColorAttachment(unsigned slot = 0) const = 0;
		virtual void BindColorAttachment(unsigned slot , unsigned index ) const = 0;
		virtual const unsigned int GetColorAttachment(unsigned index) const = 0;
		virtual const unsigned int GetColorAttachmentSize() const = 0;

		virtual const ColorAttachmentSpecification& GetColorAttachmentSpec(unsigned index) const = 0;

		static std::shared_ptr<MRTFrameBuffer> Create(const ColorAttachmentSpecification* cas, unsigned amount, const RenderBufferSpecification* rbs = nullptr);

	};
}


