package ro.stackoverflowpioneers.ConferenceManagementSystem.Controller;


import org.apache.tomcat.util.http.fileupload.IOUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import ro.stackoverflowpioneers.ConferenceManagementSystem.DTO.FileDTO;
import ro.stackoverflowpioneers.ConferenceManagementSystem.DTO.ProposalDTO;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.ProgramCommitteeMember;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.Proposal;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.AuthorRepository;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.PCMemberRepository;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.ProposalRepository;

import javax.servlet.annotation.MultipartConfig;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

@Controller
@RequestMapping("/proposals")
@CrossOrigin(origins = "*", allowedHeaders = "*")
@MultipartConfig(maxFileSize = 56177215)
public class ProposalController {
    @Autowired
    private HttpServletRequest request;

    @Autowired
    private ProposalRepository proposalRepository;

    @Autowired
    private PCMemberRepository pcMemberRepository;

    @Autowired
    private AuthorRepository authorRepository;

    @GetMapping(path = "/all")
    public @ResponseBody
    Iterable<ProposalDTO> getAllProposals() {
        return StreamSupport.stream(proposalRepository.findAll().spliterator(), false)
                .map(proposal -> new ProposalDTO(proposal.getId(), proposal.getTitle(), proposal.getAuthors(), proposal.getPaperFile(), proposal.getAbstractFile(), proposal.getStatus()))
                .collect(Collectors.toList());
    }


    @GetMapping(path = "/add")
    public @ResponseBody
    String addNewProposal(
            @RequestParam String authors,
            @RequestParam String keywords,
            @RequestParam String topics,
            @RequestParam String title,
            @RequestParam Integer idAuthor
    ) {

        Proposal proposal = new Proposal(authors, keywords, topics, null, null, title, null, idAuthor);
        proposalRepository.save(proposal);
        return "Proposal saved";
    }

    @CrossOrigin(origins = "*", allowedHeaders = "*")
    @GetMapping(path = "/accepted/{conferenceId}")
    public @ResponseBody
    Iterable<ProposalDTO> getAcceptedPapers(@PathVariable String conferenceId) {
        return StreamSupport.stream(proposalRepository.findAll().spliterator(), false)
                .filter(p -> p.isAccepted() && authorRepository.findById(p.getIdAuthor()).get().getConferenceId() == Integer.parseInt(conferenceId))
                .map(proposal -> new ProposalDTO(proposal.getId(), proposal.getTitle(), proposal.getAuthors(), proposal.getPaperFile(), proposal.getAbstractFile(), proposal.getStatus()))
                .collect(Collectors.toList());
    }

    @CrossOrigin(origins = "*", allowedHeaders = "*")
    @GetMapping(path = "/getall")
    public @ResponseBody
    Iterable<ProposalDTO> getProposals(@RequestParam String conferenceId) {
        return StreamSupport.stream(proposalRepository.findAll().spliterator(), false)
                .filter(p -> authorRepository.findById(p.getIdAuthor()).get().getConferenceId() == Integer.parseInt(conferenceId))
                .map(proposal -> new ProposalDTO(proposal.getId(), proposal.getTitle(), proposal.getAuthors(), proposal.getPaperFile(), proposal.getAbstractFile(), proposal.getStatus()))
                .collect(Collectors.toList());
    }


//    @PostMapping(path = "/addabstract", consumes = MediaType.MULTIPART_FORM_DATA_VALUE)
//    public @ResponseBody
//    String addAbstract(
//            @RequestParam String authors,
//            @RequestParam String keywords,
//            @RequestParam String topics,
//            @RequestParam String title,
//            @RequestParam Integer authorId,
//            @RequestParam MultipartFile file
//    ) {
//        Proposal proposal = new Proposal();
//        proposal.setAuthors(authors);
//        proposal.setKeywords(keywords);
//        proposal.setTopics(topics);
//        proposal.setTitle(title);
//        proposal.setStatus("not yet reviewed");
//        byte[] bytes = new byte[0];
//        try {
//            bytes = file.getBytes();
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//        System.out.println(file.getOriginalFilename());
//        Path path = Paths.get(System.getProperty("user.dir") + "\\backend\\files\\abstracts\\" + file.getOriginalFilename());
//        try {
//            Files.write(path, bytes);
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//        proposal.setIdAuthor(authorId);
//        proposal.setAbstractFile(file.getOriginalFilename());
//        proposalRepository.save(proposal);
//        return "Saved abstract";
//    }

    @PostMapping(path = "/addpaper")
    public @ResponseBody
    String addPaper(
            @RequestParam int id,
            @RequestParam String paperFile
    ) {
        Optional<Proposal> proposal = proposalRepository.findById(id);
        if (!proposal.isPresent())
            return "Proposal doesn't exist!";
        else {
            Proposal pr = proposal.get();
            pr.setPaperFile(paperFile);
            proposalRepository.save(pr);
        }

        return "Saved paper";
    }


//    @PostMapping(value = "/upload", consumes = MediaType.MULTIPART_FORM_DATA_VALUE)
//    public ResponseEntity handleFileUpload(@RequestParam MultipartFile file,
////                                   RedirectAttributes redirectAttributes,
//                                           @RequestParam String userId,
//                                           @RequestParam String fileCategory) {
//
//        byte[] bytes = new byte[0];
//        try {
//            bytes = file.getBytes();
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//        System.out.println(file.getOriginalFilename());
//        Path path = Paths.get(System.getProperty("user.dir") + "\\backend\\files\\papers\\" + file.getOriginalFilename());
//        int authorId = Integer.parseInt(userId);
//        Proposal proposal = StreamSupport.stream(proposalRepository.findAll().spliterator(), false).filter(p -> p.getIdAuthor() == authorId).findFirst().get();
//        proposal.setPaperFile(file.getOriginalFilename());
//        try {
//            Files.write(path, bytes);
//            proposalRepository.save(proposal);
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//        return ResponseEntity.ok().build();
//    }

    @GetMapping(path = "/listReviewedProposals")
    public @ResponseBody
    List<Proposal> listReviewedProposals(@RequestParam Integer id) {
        List<Proposal> result = new ArrayList<>();
        proposalRepository.findAll().forEach(prop ->
        {
            prop.getReviewers().forEach(pc -> {
                if (Objects.equals(pc.getId(), id)) {
                    result.add(prop);
                }
            });
        });

        return result;
    }

    @PostMapping(path = "/review")
    public @ResponseBody
    String addReview(@RequestParam Integer id, @RequestParam int reviewGrade) {
        Optional<Proposal> proposal = proposalRepository.findById(id);
        if (!proposal.isPresent())
            return "Proposal doesn't exist";
        Proposal finalAddedProposal = proposal.get();
        finalAddedProposal.addReview(Integer.toString(reviewGrade));

        proposalRepository.save(finalAddedProposal);
        return "Review added!";
    }

    @PostMapping(path = "/refuse")
    @Transactional
    public @ResponseBody
    String addRefuse(@RequestParam Integer id, @RequestParam Integer pcMemberId) {
        Optional<ProgramCommitteeMember> pc = pcMemberRepository.findById(pcMemberId);
        Optional<Proposal> proposal = proposalRepository.findById(id);
        pc.get().getRefusedProposals().add(proposal.get());
        proposal.get().getRefusedReview().add(pc.get());
        return "Done";
    }

    @GetMapping(path = "/getToReview/{id}")
    public @ResponseBody
    Iterable<ProposalDTO> getProposalsToReview(@PathVariable Integer id) {
        List<Proposal> list = new ArrayList<>();
        proposalRepository.findAll().forEach(list::add);
        //proposalRepository.findAll().forEach(pr -> System.out.println(pr.getRefusedReview()));
        //proposalRepository.findAll().forEach(pr -> System.out.println(pr.getReviewers()));
        return list.stream().filter(proposal -> proposal.getReviewers().stream().anyMatch(pc -> pc.getId().equals(id))).map(proposal -> new ProposalDTO(proposal.getId(), proposal.getTitle(), proposal.getAuthors(), proposal.getPaperFile(), proposal.getAbstractFile(), proposal.getStatus()))
                .collect(Collectors.toList());
    }

    @PostMapping(path = "/assignReviewer/{id}/{pcid}")
    @Transactional
    public @ResponseBody
    String assignReviewer(@PathVariable int id, @PathVariable int pcid) {
        System.out.println(id + " " + pcid);
        Optional<Proposal> proposal = proposalRepository.findById(id);
        Optional<ProgramCommitteeMember> pcMember = pcMemberRepository.findById(pcid);
        proposal.get().getReviewers().add(pcMember.get());
        pcMember.get().getReviewProposals().add(proposal.get());
        return "Done";
    }

    @GetMapping(path = "/getAuthorsProposal")
    public @ResponseBody
    List<ProposalDTO> getAuthorsProposal(@RequestParam Integer id) {

        return StreamSupport.stream(proposalRepository.findAll().spliterator(), false)
                .filter(proposal -> {
                    return Objects.equals(proposal.getIdAuthor(), id);
                })
                .map(proposal -> new ProposalDTO(proposal.getId(), proposal.getTitle(), proposal.getAuthors(), proposal.getPaperFile(), proposal.getAbstractFile(), proposal.getStatus()))
                .collect(Collectors.toList());
    }

    @RequestMapping(value = "/download-paper/{fileName}", method = RequestMethod.GET)
    public void downloadPaper(@PathVariable String fileName,
                              HttpSession session,
                              HttpServletResponse response) throws Exception {
        try {
            String filePathToBeServed = System.getProperty("user.dir") + "\\backend\\files\\papers\\" + fileName;
            File fileToDownload = new File(filePathToBeServed);
            InputStream inputStream = new FileInputStream(fileToDownload);
            response.setContentType("application/force-download");
            response.setHeader("Content-Disposition", "attachment; filename=" + fileName);
            IOUtils.copy(inputStream, response.getOutputStream());
            response.flushBuffer();
            inputStream.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @RequestMapping(value = "/download-abstract/{fileName}", method = RequestMethod.GET)
    public void downloadAbstract(@PathVariable String fileName,
                                 HttpSession session,
                                 HttpServletResponse response) throws Exception {
        try {
            String filePathToBeServed = System.getProperty("user.dir") + "\\backend\\files\\abstracts\\" + fileName;
            File fileToDownload = new File(filePathToBeServed);
            InputStream inputStream = new FileInputStream(fileToDownload);
            response.setContentType("application/force-download");
            response.setHeader("Content-Disposition", "attachment; filename=" + fileName);
            IOUtils.copy(inputStream, response.getOutputStream());
            response.flushBuffer();
            inputStream.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    @PostMapping(path = "/addabstract", consumes = MediaType.MULTIPART_FORM_DATA_VALUE)
    public @ResponseBody
    String addAbstract(
            @RequestParam String authors,
            @RequestParam String keywords,
            @RequestParam String topics,
            @RequestParam String title,
            @RequestParam Integer authorId,
            @RequestParam MultipartFile file
    )
    {
        Proposal proposal = new Proposal();
        proposal.setAuthors(authors);
        proposal.setKeywords(keywords);
        proposal.setTopics(topics);
        proposal.setTitle(title);
        proposal.setStatus("not yet reviewed");
        byte[] bytes = new byte[0];
        try {
            bytes = file.getBytes();
        } catch (IOException e) {
            e.printStackTrace();
        }
        proposal.setIdAuthor(authorId);
        proposal.setAbstFile(bytes);
        proposalRepository.save(proposal);
        return "Saved abstract";
    }

    @PostMapping(value = "/upload", consumes = MediaType.MULTIPART_FORM_DATA_VALUE)
    public ResponseEntity handleFileUpload(@RequestParam MultipartFile file,
                                           @RequestParam String userId,
                                           @RequestParam String fileCategory) {

        byte[] bytes = new byte[0];
        try {
            bytes = file.getBytes();
        } catch (IOException e) {
            e.printStackTrace();
        }
        int authorId = Integer.parseInt(userId);
        Proposal proposal = StreamSupport.stream(proposalRepository.findAll().spliterator(), false).filter(p -> p.getIdAuthor() == authorId).findFirst().get();
        proposal.setPapFile(bytes);
        proposalRepository.save(proposal);
        return ResponseEntity.ok().build();
    }

    @GetMapping(value = "/getAbstract/{id}")
    public @ResponseBody
    FileDTO getAbstract(@PathVariable int id)
    {
        byte []arr = proposalRepository.findById(id).get().getAbstFile();
        return new FileDTO(Base64.getEncoder().encodeToString(arr));
    }

    @GetMapping(value = "/getPaper/{id}")
    public @ResponseBody
    FileDTO getPaper(@PathVariable int id)
    {
        byte []arr = proposalRepository.findById(id).get().getPapFile();
        return new FileDTO(Base64.getEncoder().encodeToString(arr));
    }


}
