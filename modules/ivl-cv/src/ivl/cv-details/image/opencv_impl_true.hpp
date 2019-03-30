/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License 
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the terms 
   of the GNU General Public License version 2 as published by the Free 
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License 
   and a copy of the GNU Lesser General Public License along 
   with ivl. If not, see <http://www.gnu.org/licenses/>. */


namespace image_details {

template<class P>
struct cv<true, P>
{
	typedef IplImage iplimage_t;

	template<class T, class S>
	static void load(image<T, S>& im, const std::string& filename, image_channels channels);

	template<class T, class S>
	static void save(const image<T, S>& im, const std::string& filename);

	template <class S>
	struct type
	{
		template <class T, class D>
		static void copy_from(image<T, D>& im, const IplImage* src);
	};

	template <class T, class D>
	static void copy_from(image<T, D>& im, const IplImage* src);

	template <class T, class D>
	static void copy_to(const image<T, D>& im, IplImage* dest);

	template <class T, class D>
	static IplImage* ipl(const image<T, D>& im);
};


static const int ic_map[3] = { CV_LOAD_IMAGE_UNCHANGED, CV_LOAD_IMAGE_GRAYSCALE, CV_LOAD_IMAGE_COLOR };
static const int interpolation_map[4] = { CV_INTER_NN, CV_INTER_LINEAR, CV_INTER_AREA, CV_INTER_CUBIC };
static const int warp_map[2] = { CV_WARP_FILL_OUTLIERS, CV_WARP_INVERSE_MAP };

//	extern int ic_map[3];
//	extern int interpolation_map[4];
//	extern int warp_map[2];



template <class P>
template <class T, class D>
void cv<true, P>::load(image<T, D>& im, const std::string& filename, image_channels channels)
{
	// channels: ic_auto, ic_mono or ic_color
	int cvflags = image_details::ic_map[channels];
	// load the image file into a temporary IplImage
	IplImage *iplsrc = cvLoadImage(filename.c_str(), cvflags);
	// verify the existance of the file
	if(!iplsrc) throw ecomp();
	//TODO: replace ecomp with an i/o exception when exceptions are ready.
	im = iplsrc;
	// Release temporary IplImage
	cvReleaseImage(&iplsrc);
}

template<class P>
template <class T, class D>
void cv<true, P>::save(const image<T, D>& im, const std::string& filename) 
{
	IplImage *ipl = im.ipl();
	cvSaveImage(filename.c_str(), ipl);
	cvReleaseImage(&ipl);
}

// returns the OpenCV type for T (single channel)
template <class T>
inline int cv_type()
{
	return CV_8UC1;
}
template <>
inline int cv_type<int8_t>()
{
	return CV_8SC1;
}
template <>
inline int cv_type<uint8_t>()
{
	return CV_8UC1;
}
template <>
inline int cv_type<int16_t>()
{
	return CV_16SC1;
}
template <>
inline int cv_type<uint16_t>()
{
	return CV_16UC1;
}
template <>
inline int cv_type<int32_t>()
{
	return CV_32SC1;
}
template <>
inline int cv_type<float>()
{
	return CV_32FC1;
}
template <>
inline int cv_type<double>()
{
	return CV_64FC1;
}
// text end

// returns the OpenCV IPL_DEPTH for T
template <class T>
inline int ipl_depth()
{
	return IPL_DEPTH_8U;
}
template <>
inline int ipl_depth<int8_t>()
{
	return IPL_DEPTH_8S;
}
template <>
inline int ipl_depth<uint8_t>()
{
	return IPL_DEPTH_8U;
}
template <>
inline int ipl_depth<int16_t>()
{
	return IPL_DEPTH_16S;
}
template <>
inline int ipl_depth<uint16_t>()
{
	return IPL_DEPTH_16U;
}
template <>
inline int ipl_depth<int32_t>()
{
	return IPL_DEPTH_32S;
}
template <>
inline int ipl_depth<float>()
{
	return IPL_DEPTH_32F;
}
template <>
inline int ipl_depth<double>()
{
	return IPL_DEPTH_64F;
}

inline CvSize cv_size(const size_array& a)
{
	CvSize sz;
	sz.width = int(a[0]);
	sz.height = int(a[1]);
	return sz;
}

inline CvSize cv_size(size_t width, size_t height)
{
	CvSize sz;
	sz.width = int(width);
	sz.height = int(height);
	return sz;
}

template <class T>
inline CvScalar to_cvscalar(const ivl::color<T>& c)
{
	if(c.length()==1) return cvScalar(c[0]);
	else if(c.length()==2) return cvScalar(c[0],c[1]);
	else if(c.length()==3) return cvScalar(c[0],c[1],c[2]);
	else if(c.length()==4) return cvScalar(c[0],c[1],c[2],c[3]);
	else return cvScalar(0);
}

template <class T>
inline ivl::color<T> from_cvscalar(CvScalar s, int length)
{
	ivl::color<T> col(length);
	for(int i = 0; i < length; i++) {
		col[i] = s.val[i];
	}
	return col;
}

//! converts image data from an IplImage into an initialized ivl::image
//  conversion of int(0 - 255)<->float(0.0 - 1.0)
template <class P>
template <class S>
template <class T, class D>
void cv<true, P>::type<S>::copy_from(image<T, D>& im, const IplImage* src)
{
	T* ptr = im.c_ptr();
	// all variables below, except from those with names with im_ prefix,
	// refer to IplImage data
	size_t step = src->nChannels * sizeof(S);
	size_t im_height = src->height;
	for(size_t i = 0; i < (size_t)src->nChannels; i++) {
		T* im_channel_ptr = ptr + i * ( src->width * src->height);
		size_t channel_offset = i * sizeof(S);
		size_t rowend_offset = ( src->width * src->nChannels *
			sizeof(S)) + channel_offset;
		for(char* ipl_rowptr = src->imageData;
		ipl_rowptr - src->imageData < src->imageSize;
		ipl_rowptr += src->widthStep) {
			T* im_row_ptr = im_channel_ptr++;
			char* ipl_rowend = ipl_rowptr + rowend_offset;
			for(char* ipl_ptr = ipl_rowptr + channel_offset;
			ipl_ptr != ipl_rowend; ipl_ptr += step) {
				*(im_row_ptr) = (T)
				image_details::value_conv(*((S*)ipl_ptr), T(0));
				im_row_ptr += im_height;
			}
		}
	}
}

//! converts image data from an ivl::image into an initialized IplImage
//  conversion of int(0 - 255)<->float(0.0 - 1.0)
template <class P>
template <class T, class D>
void cv<true, P>::copy_to(const image<T, D>& im, IplImage* ipl)
{
	const T* srcptr = im.c_ptr();
	// all variables below, except from those with names with im_ prefix,
	// refer to IplImage data
	size_t step = ipl->nChannels * sizeof(T);
	size_t im_height = ipl->height;
	for(size_t i = 0; i < (size_t)ipl->nChannels; i++)
	{
		const T* im_channel_ptr = srcptr +
			i * ( ipl->width * ipl->height );
		size_t channel_offset = i * sizeof(T);
		size_t rowend_offset = (ipl->width * ipl->nChannels *
			sizeof(T)) + channel_offset;
		for(char* ipl_rowptr = ipl->imageData;
		ipl_rowptr - ipl->imageData < ipl->imageSize;
		ipl_rowptr += ipl->widthStep) {
			const T* im_row_ptr = im_channel_ptr++;
			char* ipl_rowend = ipl_rowptr + rowend_offset;
			for(char* ipl_ptr = ipl_rowptr + channel_offset;
			ipl_ptr != ipl_rowend; ipl_ptr += step) {
				*((T*)ipl_ptr) = *(im_row_ptr);
				im_row_ptr += im_height;
			}
		}
	}
}

//! creates an IplImage* from an ivl::image<T>
template <class P>
template <class T, class D>
IplImage* cv<true, P>::ipl(const image<T, D>& im)
{
	CvSize sz = image_details::cv_size(arr(im.width(), im.height()));
	IplImage* ipl = cvCreateImage(sz, image_details::ipl_depth<T>(),
		int(im.channels()));
	copy_to(im, ipl);

	return ipl;
}

//! reads the data from the IplImage into the current image
template <class P>
template <class T, class D>
void cv<true, P>::copy_from(image<T, D>& im, const IplImage* src)
{
	im.resize(idx(src->height, src->width, src->nChannels));

	switch(src->depth)
	{
	case IPL_DEPTH_8U: type<uint8_t>::copy_from (im, src); break;
	case IPL_DEPTH_8S: type<int8_t>::copy_from (im, src); break;
	case IPL_DEPTH_16U: type<uint16_t>::copy_from (im, src); break;
	case IPL_DEPTH_16S: type<int16_t>::copy_from (im, src); break;
	case IPL_DEPTH_32S: type<int32_t>::copy_from (im, src); break;
	case IPL_DEPTH_32F: type<float>::copy_from (im, src); break;
	case IPL_DEPTH_64F: type<double>::copy_from (im, src); break;
	default: throw new ecomp(); break;
	}
	//TODO: wipe comments
	//return static_cast<typename image<T, D>::derived_type&>(*this);
	//MSVC: return this->derived();
}

} // namespace image_details

