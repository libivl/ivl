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

namespace ivl {

namespace lina_details {



template<class T>
void unroll<T>::unroll_vr(
		const std::complex<T>* w,
		array_2d<T> &vr,
		std::complex<T>* v)
{
	T* vr_ptr = vr.c_ptr();
	const size_t m = vr.rows();
	const size_t n = vr.columns();

	for(size_t j = 0; j < n; j++) {
		// If the j-th eigenvalue is real,
		if(w[j].imag() == 0.0) {

		// then v(j) = VR(:,j), the j-th column of VR.
			std::complex<T>* dst = v + j * m; // v(:,j)
			const T* src = vr_ptr + j * m; // VR(:,j)
			const T* src_end = src + m;

			while(src != src_end)
				*dst++ = std::complex<T>(*src++, 0.0);

		} else {
			// If the j-th and (j+1)-st eigenvalues form a complex
			// conjugate pair, then:
			// v(j)   = VR(:,j) + i*VR(:,j+1)
			// v(j+1) = VR(:,j) - i*VR(:,j+1).
			if (j < n - 1) {

				std::complex<T>* dst = v + j * m; // v(:,j)
				std::complex<T>* dst_plus = v + j * m; // v(:,j+1)
				const T* src = vr_ptr + j * m; // VR(:,j)
				const T* src_plus = vr_ptr + (j + 1) * m; // VR(:,j+1)

				for (size_t i = 0; i < m; ++i) {

					*dst++ = std::complex<T>(*src, *src_plus);
					*dst_plus++ = std::complex<T>(*src++, *src_plus++);
				}
				j++;
			}
		}
	}
}

}; /*namespace lina_details */

}; /*namespace ivl */
