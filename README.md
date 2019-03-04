# Prepare
```Shell
mkdir build
cd build
conan install ..
```

# Build
```Shell
cmake ..
make
```

# Install
```Shell
sudo make install
```

# Run
```Shell
systemctl daemon-reload
systemctl start process_monitor
```
