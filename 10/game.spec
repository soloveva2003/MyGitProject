Name:           game
Version:        1.0
Release:        1%{?dist}
Summary:        A simple game
Group:          Games/Entertainment 

License:        GPLv3+
URL:            https://github.com/
Source0:        game-1.0.tar

BuildRequires:  gcc-c++
BuildRequires:  ncurses-devel
Requires:       ncurses

%description
A simple game implemented in C++.

%prep
%setup -q

%build
make %{?_smp_mflags}

%install
mkdir -p %{buildroot}/usr/local/bin
install -m 755 game %{buildroot}/usr/local/bin/game

%files
/usr/local/bin/game

%changelog
* Thu Feb 26 2025 <salo.mail@ru> - 1.0-1
- Initial package.
