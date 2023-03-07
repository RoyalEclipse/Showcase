package com.semestral.eshop;

import com.semestral.eshop.domain.SiteUser;
import com.semestral.eshop.repository.UserRepository;
import com.semestral.eshop.service.UserServiceImpl;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.boot.test.web.client.TestRestTemplate;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;

import java.util.Optional;

import static org.assertj.core.api.AssertionsForClassTypes.assertThat;
import static org.mockito.Mockito.when;

@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
public class UserControllerSystemTest {
    @Autowired
    TestRestTemplate testRestTemplate;

    @MockBean
    UserRepository userRepository;

    @InjectMocks
    UserServiceImpl userService;

    @Test
    public void testLogin() throws Exception{

        Long id = 69L;
        String password = "1234";
        String email = "email";

        Optional<SiteUser> expectedRes = Optional.of( new SiteUser() );
        expectedRes.get().setId(id);
        expectedRes.get().setPassword(password);
        expectedRes.get().setEmail(email);
        when(userRepository.findByPasswordAndEmail(password,email))
                .thenReturn( expectedRes );

        ResponseEntity<Long> response = testRestTemplate
                        .getForEntity("/user/" + email + "/" + password, Long.class);

        assertThat(response.getStatusCode()).isEqualTo(HttpStatus.OK);
        assertThat(response.getBody()).isEqualTo(id);
    }
}
