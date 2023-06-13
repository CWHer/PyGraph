import setuptools


if __name__ == "__main__":
    setuptools.setup(
        name="cgraph",
        version="1.0",
        author="cwher",
        author_email="cwher@outlook.com",
        description="A high-performance graph library",
        license="GPLv3",
        platforms="Linux",
        packages=["cgraph"],
        package_data={"cgraph": ["*.so"]},
        install_requires=["numpy"],
    )
