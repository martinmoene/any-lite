from conans import ConanFile

class AnyLiteConan(ConanFile):
    version = "0.1.0"
    name = "any-lite"
    description = "A single-file header-only C++17-like any, a type-safe container for single values of any type for C++98, C++11 and later"
    license = "Boost Software License - Version 1.0. http://www.boost.org/LICENSE_1_0.txt"
    url = "https://github.com/martinmoene/any-lite.git"
    exports_sources = "include/nonstd/*", "LICENSE.txt"
    build_policy = "missing"    
    author = "Martin Moene"

    def build(self):
        """Avoid warning on build step"""
        pass

    def package(self):
        """Provide pkg/include/nonstd/*.hpp"""
        self.copy("*.hpp")

    def package_info(self):
        self.info.header_only()
