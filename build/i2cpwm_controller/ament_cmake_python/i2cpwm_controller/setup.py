from setuptools import find_packages
from setuptools import setup

setup(
    name='i2cpwm_controller',
    version='0.5.1',
    packages=find_packages(
        include=('i2cpwm_controller', 'i2cpwm_controller.*')),
)
