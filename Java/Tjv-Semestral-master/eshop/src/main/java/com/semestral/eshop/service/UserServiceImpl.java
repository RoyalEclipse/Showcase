package com.semestral.eshop.service;

import com.semestral.eshop.domain.SiteUser;
import com.semestral.eshop.repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class UserServiceImpl implements UserService {

    private final UserRepository userRepository;

    @Autowired
    public UserServiceImpl(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    @Override
    public SiteUser create(SiteUser toAdd) {
        return userRepository.save( toAdd );
    }

    @Override
    public SiteUser update(SiteUser toUpdate) {
        return userRepository.save(toUpdate);
    }

    @Override
    public void delete(Long toDelete) {
        userRepository.deleteById(toDelete);
    }

    @Override
    public Optional<SiteUser> findById(Long id) {
        return userRepository.findById(id);
    }

    @Override
    public List<SiteUser> findAll() {
        return userRepository.findAll();
    }

    @Override
    public Optional<SiteUser> findByPasswordAndEmail( String password, String email ){
        return userRepository.findByPasswordAndEmail(password,email);
    }
}
