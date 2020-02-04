package controller;

import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.*;
import model.PrgState;
import model.statement.IStmt;
import model.type.RefType;
import model.type.Type;
import model.value.RefValue;
import model.value.Value;
import repository.IRepository;

import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Controller {
    private IRepository repo;
    private ExecutorService executor;

    public Controller(IRepository repo) {
        this.repo = repo;
        executor = Executors.newFixedThreadPool(3);
    }

    List<PrgState> removeCompletedPrograms(List<PrgState> programList) {
        return programList.stream().filter(prog -> prog.isNotCompleted())
                                   .collect(Collectors.toList());
    }

    Map<Integer, Value> garbageCollector(List<Integer> addresses, Map<Integer, Value> heap) {
        return heap.entrySet().stream()
               .filter(elem -> addresses.contains(elem.getKey()))
               .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    List<Integer> extractAllValidAddresses(List<Integer> symTableAddressesList, Map<Integer, Value> heapDictionary) {
        Set<Map.Entry<Integer, Value>> heapEntrySet = heapDictionary.entrySet();
        LinkedList<Integer> indirectAddressesList = new LinkedList<Integer>(symTableAddressesList);

        boolean doneExtracting = false;
        while (!doneExtracting) {
            doneExtracting = true;
            List <Integer> currentIndirectPhaseAddresses = heapEntrySet.stream()
                                                           .filter(entry -> indirectAddressesList.contains(entry.getKey()))
                                                           .filter(entry -> entry.getValue() instanceof RefValue)
                                                           .map(entry -> {RefValue v = (RefValue) entry.getValue();
                                                                          return v.getAddress();})
                                                           .filter(entry -> !indirectAddressesList.contains(entry))
                                                           .collect(Collectors.toList());

            if (!currentIndirectPhaseAddresses.isEmpty()) {
                doneExtracting = false;
                indirectAddressesList.addAll(currentIndirectPhaseAddresses);
            }
        }
        return indirectAddressesList;
    }

    private List<Integer> getSymTableAddresses(Collection<Value> symTableValues) {
        return symTableValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {RefValue v1 = (RefValue) v; return v1.getAddress();})
                .collect(Collectors.toList());
    }

    List<Integer> getAddressesFromSymTableAndHeap(Map<Integer, Value> heapDictionary) {
        List<Integer> symTableAddressesList = repo.getPrgList().stream()
                                                               .map(p -> getSymTableAddresses(p.getSymTable().getContent().values()))
                                                               .reduce(Stream.of(0).collect(Collectors.toList()),
                                                                       (acc, item) -> Stream.concat(acc.stream(), item.stream())
                                                                                            .collect(Collectors.toList()));
        return extractAllValidAddresses(symTableAddressesList, heapDictionary);
    }

    void collectGarbage() {
        IMyHeap<Value> heap = repo.getProgramHeap();
        heap.setContent(garbageCollector(getAddressesFromSymTableAndHeap(heap.getContent()),
                                         heap.getContent()));
    }

    void oneStepForAllPrograms(List<PrgState> list) throws MyException {
        List<Callable<PrgState>> callList = list.stream().map((PrgState program) -> (Callable<PrgState>)(() -> {return program.oneStep();}))
                                                         .collect(Collectors.toList());
        List<PrgState> newList = null;
        try {
            newList = executor.invokeAll(callList).stream().map(future -> {
                                                                     try {
                                                                         return future.get();
                                                                     } catch (InterruptedException | ExecutionException e) {
                                                                         repo.addError(e.getMessage());
                                                                         return null;
                                                                     }
                                                                 })
                                                                 .filter(p -> p != null)
                                                                 .collect(Collectors.toList());
        } catch (InterruptedException e) {
            throw new MyException(e.getMessage());
        }
        if (repo.errorThrown()) {
            throw new MyException(repo.getError());
        }
        list.addAll(newList);

        list.forEach(program -> {try {repo.logPrgStateExec(program);} catch(MyException ignored) {}});
        repo.setPrgList(list);
    }

    public void evaluateOnlyOneStep() throws MyException {
        List<PrgState> list = removeCompletedPrograms(repo.getPrgList());
        collectGarbage();
        oneStepForAllPrograms(list);
        list = removeCompletedPrograms(repo.getPrgList());
        repo.setPrgList(list);
        if (list.isEmpty()) {
            executor.shutdownNow();
        }
    }

    public List<PrgState> getProgramList() {
        return repo.getPrgList();
    }

    public void evaluateOneStep() throws MyException {
        List<PrgState> list = removeCompletedPrograms(repo.getPrgList());
        list.forEach(program -> {try {repo.logPrgStateExec(program);} catch(MyException ignored) {}});
        while (!list.isEmpty()) {
            collectGarbage();
            oneStepForAllPrograms(list);
            list = removeCompletedPrograms(repo.getPrgList());
        }
        repo.getPrgList().forEach(program -> {try {repo.logPrgStateExec(program);} catch(MyException ignored) {}});
        executor.shutdownNow();
        repo.setPrgList(list);
    }

    public void restartProgram() {
        executor = Executors.newFixedThreadPool(3);
        repo.restartProgram();
    }

    public void typecheckOriginalProgram() throws TypeCheckException {
        MyDictionary<String, Type> typeEnvironment = new MyDictionary<String, Type>();
        IStmt originalProgram = repo.getOriginalProgram();
        originalProgram.typecheck(typeEnvironment);
    }

    @Override
    public String toString() {
        return repo.getOriginalProgram().toString();
    }
}
