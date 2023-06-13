import setuptools


if __name__ == "__main__":
    setuptools.setup(
        name="cgraph",
        version="1.0",
        author="cwher",
        author_email="cwher@outlook.com",
        description="A high-performance graph library",
        classifiers=[
            "Programming Language :: Python :: 3",
            "License :: OSI Approved :: GNU General Public License v3 (GPLv3)",
            "Operating System :: POSIX :: Linux",
        ],
        packages=["cgraph"],
        package_data={"cgraph": ["*.so"]},
        has_ext_modules=lambda: True,
        install_requires=["numpy"],
    )
