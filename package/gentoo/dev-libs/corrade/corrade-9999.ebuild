# Copyright 1999-2014 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

EAPI=5

EGIT_REPO_URI="git://github.com/mosra/corrade.git"

inherit cmake-utils git-r3

DESCRIPTION="C++11 Multiplatform plugin management and utility library"
HOMEPAGE="http://mosra.cz/blog/corrade.php"

LICENSE="MIT"
SLOT="0"
KEYWORDS="~amd64 ~x86"
IUSE=""

RDEPEND="
	dev-util/cmake
"
DEPEND="${RDEPEND}"

src_configure() {
	local mycmakeargs=(
		-DCMAKE_INSTALL_PREFIX="${EPREFIX}/usr"
		-DCMAKE_BUILD_TYPE=Release
	)
	cmake-utils_src_configure
}

# kate: replace-tabs off;
