Name:           game
Version:        1.0
Release:        alt1
Summary:        A simple game
Group:          Games/Arcade 

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
mkdir -p %{buildroot}/usr/bin
install -m 755 game %{buildroot}/usr/bin/game

%files
/usr/bin/game

%changelog
* Thu Feb 26 2025 <salo.mail@ru> - 1.0-1
- Initial package.
